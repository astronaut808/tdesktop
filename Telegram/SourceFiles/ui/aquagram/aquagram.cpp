#include "ui/aquagram/aquagram.h"

#include "ui/style/style_core_palette.h"
#include "ui/widgets/fields/input_field.h"
#include "ui/widgets/buttons.h"

#include <QtCore/QEvent>
#include <QtCore/QVariant>
#include <QtGui/QFontDatabase>
#include <QtGui/QLinearGradient>
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <QtGui/QPalette>
#include <QtWidgets/QWidget>

#include "styles/style_aquagram.h"

namespace Ui::Aqua {
namespace {

constexpr auto kFieldMarginsProperty = "aquagramRequestedFieldMargins";

class FocusObserver final : public QObject {
public:
	explicit FocusObserver(QWidget *widget);

private:
	bool eventFilter(QObject *object, QEvent *event) override;

};

FocusObserver::FocusObserver(QWidget *widget) : QObject(widget) {
	widget->installEventFilter(this);
}

bool FocusObserver::eventFilter(QObject *object, QEvent *event) {
	if (event->type() == QEvent::FocusIn
		|| event->type() == QEvent::FocusOut
		|| event->type() == QEvent::EnabledChange) {
		static_cast<QWidget*>(object)->update();
	}
	return false;
}

QColor Color(const QString &value) {
	return QColor(value);
}

QColor WithOpacity(QColor color, double opacity) {
	color.setAlphaF(opacity);
	return color;
}

QRectF Inset(QRectF rect, double amount) {
	return rect.adjusted(amount, amount, -amount, -amount);
}

bool HasAquaFieldStyle(const style::InputField &style) {
	const auto lightOpaque = [](const style::color &color) {
		return color->c.alpha() == 255
			&& color->c.lightnessF() >= st::aquaMetrics.lightThreshold;
	};
	return (style.border || style.borderRadius)
		&& lightOpaque(style.textBg)
		&& lightOpaque(style.textBgActive);
}

QLinearGradient ButtonGradient(QRectF rect, bool primary, bool pressed) {
	const auto &c = st::aquaColors;
	auto gradient = QLinearGradient(rect.topLeft(), rect.bottomLeft());
	gradient.setColorAt(0., Color(pressed ? c.pressedTop
		: primary ? c.blueTop : c.silverTop));
	gradient.setColorAt(st::aquaMetrics.upperStop,
		Color(pressed ? c.pressedUpper
			: primary ? c.blueUpper : c.silverUpper));
	gradient.setColorAt(st::aquaMetrics.lowerStop,
		Color(pressed ? c.pressedMiddle
			: primary ? c.blueMiddle : c.silverMiddle));
	gradient.setColorAt(1., Color(pressed ? c.pressedBottom
		: primary ? c.blueBottom : c.silverBottom));
	return gradient;
}

void FocusRing(QPainter &p, QRectF rect, double radius, double degree) {
	const auto &m = st::aquaMetrics;
	p.setBrush(Qt::NoBrush);
	p.setPen(QPen(WithOpacity(Color(st::aquaColors.focus),
		degree * m.focusOpacity), m.focusWidth));
	p.drawRoundedRect(rect, radius, radius);
}

void SetColor(QLatin1String name, const QString &value) {
	const auto c = Color(value);
	const auto result = style::main_palette::setColor(
		name,
		c.red(),
		c.green(),
		c.blue(),
		c.alpha());
	Expects(result == style::palette::SetResult::Ok
		|| result == style::palette::SetResult::Duplicate);
}

} // namespace

QString ResolveFontFamily(const QString &requested) {
	if (!requested.isEmpty()) {
		return requested;
	}
#ifdef Q_OS_MAC
	const auto historical = u"Lucida Grande"_q;
	if (QFontDatabase::families().contains(historical)) {
		return historical;
	}
#endif // Q_OS_MAC
	return requested;
}

bool IsLight() {
	return st::windowBg->c.lightnessF() >= st::aquaMetrics.lightThreshold;
}

void ApplyPalette() {
	if (!IsLight()) {
		return;
	}
	const auto &c = st::aquaColors;
	for (const auto name : {
		"windowBg", "boxBg", "boxSearchBg", "filterInputActiveBg",
		"filterInputInactiveBg", "msgInBg", "historyComposeAreaBg" }) {
		SetColor(QLatin1String(name), c.contentPrimary);
	}
	for (const auto name : {
		"windowBgOver", "menuBgOver", "dialogsBgOver", "boxDividerBg" }) {
		SetColor(QLatin1String(name), c.contentSecondary);
	}
	SetColor(QLatin1String("dialogsBg"), c.sidebarTint);
	SetColor(QLatin1String("sideBarBg"), c.metalMiddle);
	SetColor(QLatin1String("sideBarBgActive"), c.selectionBottom);
	SetColor(QLatin1String("sideBarBgRipple"), c.metalBottom);
	for (const auto name : {
		"sideBarTextFg", "sideBarIconFg" }) {
		SetColor(QLatin1String(name), c.secondaryText);
	}
	for (const auto name : {
		"sideBarTextFgActive", "sideBarIconFgActive" }) {
		SetColor(QLatin1String(name), c.text);
	}
	for (const auto name : {
		"sideBarBadgeBg", "sideBarBadgeBgActive", "sideBarBadgeBgMutedActive" }) {
		SetColor(QLatin1String(name), c.blueDark);
	}
	SetColor(QLatin1String("sideBarBadgeBgMuted"), c.secondaryText);
	for (const auto name : {
		"windowFg", "windowFgOver", "windowBoldFg", "windowBoldFgOver",
		"boxTextFg", "boxTitleFg", "dialogsNameFg", "dialogsNameFgOver",
		"activeButtonFg", "activeButtonFgOver", "activeButtonSecondaryFg",
		"activeButtonSecondaryFgOver", "lightButtonFg",
		"lightButtonFgOver" }) {
		SetColor(QLatin1String(name), c.text);
	}
	for (const auto name : {
		"windowSubTextFg", "windowSubTextFgOver", "placeholderFg",
		"placeholderFgActive", "dialogsTextFg", "dialogsTextFgOver",
		"dialogsDateFg", "dialogsDateFgOver" }) {
		SetColor(QLatin1String(name), c.secondaryText);
	}
	for (const auto name : {
		"windowBgActive", "activeButtonBg", "activeButtonBgOver",
		"dialogsUnreadBg", "dialogsUnreadBgOver", "historySendIconFg" }) {
		SetColor(QLatin1String(name), c.blue);
	}
	for (const auto name : {
		"windowActiveTextFg", "historyLinkInFg", "historyLinkOutFg" }) {
		SetColor(QLatin1String(name), c.link);
	}
	SetColor(QLatin1String("inputBorderFg"), c.fieldBorder);
	SetColor(QLatin1String("activeLineFg"), c.focus);
	SetColor(QLatin1String("filterInputBorderFg"), c.focus);
	SetColor(QLatin1String("lightButtonBg"), c.contentSecondary);
	SetColor(QLatin1String("lightButtonBgOver"), c.contentSecondary);
	SetColor(QLatin1String("menuSeparatorFg"), c.separator);
	SetColor(QLatin1String("dialogsBgActive"), c.selectionBottom);
	for (const auto name : {
		"dialogsNameFgActive", "dialogsTextFgActive", "dialogsDateFgActive",
		"dialogsTextFgServiceActive", "dialogsChatIconFgActive" }) {
		SetColor(QLatin1String(name), c.text);
	}
	SetColor(QLatin1String("topBarBg"), c.metalMiddle);
}

void UpdateFieldPalette(QPalette &palette, const style::InputField &style) {
	if (IsLight() && HasAquaFieldStyle(style)) {
		palette.setColor(QPalette::Disabled, QPalette::Text,
			Color(st::aquaColors.disabledText));
	}
}

void WatchFocus(QWidget *widget) {
	new FocusObserver(widget);
}

bool PaintButton(
		QPainter &p,
		QRect rect,
		const style::RoundButton &style,
		bool hovered,
		bool pressed,
		bool enabled,
		bool focused) {
	const auto primary = (style.textBg == st::activeButtonBg);
	const auto secondary = (style.textBg == st::lightButtonBg);
	const auto &m = st::aquaMetrics;
	if (!IsLight()
		|| (!primary && !secondary)
		|| rect.height() < m.buttonMinHeight) {
		return false;
	}
	p.save();
	p.setRenderHint(QPainter::Antialiasing);
	const auto body = Inset(QRectF(rect), m.focusInset);
	const auto radius = std::min<double>(m.buttonRadius, body.height() / 2.);
	if (focused && enabled) {
		FocusRing(p, Inset(QRectF(rect), m.line), radius, 1.);
	}
	p.setPen(Qt::NoPen);
	p.setBrush(WithOpacity(Color(st::aquaColors.metalBorder), m.focusOpacity));
	p.drawRoundedRect(body.translated(0, m.shadowOffset), radius, radius);
	auto gradient = ButtonGradient(body, primary, pressed && enabled);
	if (!enabled) {
		gradient = QLinearGradient(body.topLeft(), body.bottomLeft());
		gradient.setColorAt(0., Color(st::aquaColors.disabledTop));
		gradient.setColorAt(1., Color(st::aquaColors.disabledBottom));
	}
	p.setBrush(gradient);
	p.setPen(QPen(Color(primary && enabled
		? st::aquaColors.buttonBorder : st::aquaColors.silverBorder), m.line));
	p.drawRoundedRect(body, radius, radius);
	p.setBrush(Qt::NoBrush);
	p.setPen(QPen(WithOpacity(Color(st::aquaColors.highlight),
		pressed && enabled ? m.focusOpacity : enabled ? 0.8 : 0.5), m.line));
	p.drawRoundedRect(Inset(body, m.line), radius - m.line, radius - m.line);
	if (hovered && enabled && !pressed) {
		p.setPen(QPen(Color(st::aquaColors.focus), m.line));
		p.drawRoundedRect(body, radius, radius);
	}
	p.restore();
	return true;
}

QColor ButtonTextColor(
		const style::RoundButton &style,
		bool hovered,
		bool pressed,
		bool enabled) {
	return pressed && enabled
		? Color(st::aquaColors.highlight)
		: (hovered || pressed ? style.textFgOver : style.textFg)->c;
}

double ContentOpacity(bool enabled) {
	return enabled ? 1. : st::aquaMetrics.disabledOpacity;
}

QMargins FieldTextMargins(const style::InputField &style, bool aqua) {
	auto margins = style.textMargins;
	if (aqua && HasAquaFieldStyle(style)) {
		margins.setLeft(std::max(margins.left(), st::aquaMetrics.fieldPadding));
		margins.setRight(std::max(margins.right(), st::aquaMetrics.fieldPadding));
	}
	return margins;
}

QMargins ApplyFieldTextMargins(
		QWidget *widget,
		const style::InputField &style,
		QMargins requested) {
	widget->setProperty(kFieldMarginsProperty, QVariant::fromValue(requested));
	if (IsLight() && HasAquaFieldStyle(style)) {
		requested.setLeft(std::max(requested.left(), st::aquaMetrics.fieldPadding));
		requested.setRight(std::max(requested.right(), st::aquaMetrics.fieldPadding));
	}
	return requested;
}

QMargins RequestedFieldTextMargins(
		QWidget *widget,
		const style::InputField &style) {
	const auto value = widget->property(kFieldMarginsProperty);
	return value.isValid() ? value.value<QMargins>() : style.textMargins;
}

bool PaintField(
		QPainter &p,
		QRect rect,
		const style::InputField &style,
		double error,
		double focus,
		bool enabled) {
	if (!IsLight() || !HasAquaFieldStyle(style)) {
		return false;
	}
	const auto &m = st::aquaMetrics;
	p.save();
	p.setRenderHint(QPainter::Antialiasing);
	if (!style.borderRadius) {
		p.fillRect(rect, style.textBg);
	}
	auto body = Inset(QRectF(rect), m.focusInset);
	if (style.placeholderScale > 0.) {
		body.setTop(std::max<double>(body.top(),
			style.textMargins.top() - m.fieldPadding));
	}
	const auto radius = style.borderRadius
		? std::min<double>(style.borderRadius, body.height() / 2.)
		: m.fieldRadius;
	if (enabled && focus > 0.) {
		FocusRing(p, body, radius, focus);
	}
	const auto border = error > 0.
		? anim::color(Color(st::aquaColors.fieldBorder), Color(st::aquaColors.error), error)
		: focus > 0. && enabled
		? anim::color(Color(st::aquaColors.fieldBorder), Color(st::aquaColors.focus), focus)
		: Color(st::aquaColors.fieldBorder);
	p.setPen(QPen(border, m.line));
	p.setBrush(Color(enabled ? st::aquaColors.contentPrimary
		: st::aquaColors.contentSecondary));
	p.drawRoundedRect(body, radius, radius);
	auto path = QPainterPath();
	path.addRoundedRect(Inset(body, m.line), radius, radius);
	p.setClipPath(path, Qt::IntersectClip);
	auto inset = QLinearGradient(body.topLeft(),
		body.topLeft() + QPointF(0, m.fieldPadding));
	inset.setColorAt(0., Color(enabled ? st::aquaColors.fieldShadow
		: st::aquaColors.disabledTop));
	inset.setColorAt(1., Color(enabled ? st::aquaColors.contentPrimary
		: st::aquaColors.disabledBottom));
	p.fillRect(body, inset);
	p.restore();
	return true;
}

bool PaintMetal(QPainter &p, QRect rect) {
	if (!IsLight()) {
		return false;
	}
	p.save();
	auto gradient = QLinearGradient(rect.topLeft(), rect.bottomLeft());
	gradient.setColorAt(0., Color(st::aquaColors.metalTop));
	gradient.setColorAt(0.5, Color(st::aquaColors.metalMiddle));
	gradient.setColorAt(1., Color(st::aquaColors.metalBottom));
	p.fillRect(rect, gradient);
	p.setPen(QPen(WithOpacity(Color(st::aquaColors.grain),
		st::aquaMetrics.grainOpacity), st::aquaMetrics.line));
	for (auto y = rect.top(); y < rect.bottom(); y += st::aquaMetrics.grainPitch) {
		p.drawLine(rect.left(), y, rect.right(), y);
	}
	p.fillRect(QRect(rect.topLeft(), QSize(rect.width(), st::aquaMetrics.line)),
		Color(st::aquaColors.highlight));
	p.fillRect(QRect(rect.left(), rect.y() + rect.height() - st::aquaMetrics.line,
		rect.width(), st::aquaMetrics.line), Color(st::aquaColors.metalBorder));
	p.restore();
	return true;
}

void PaintSelection(QPainter &p, QRect rect, bool activeWindow) {
	p.save();
	auto gradient = QLinearGradient(rect.topLeft(), rect.bottomLeft());
	gradient.setColorAt(0., Color(activeWindow
		? st::aquaColors.selectionTop : st::aquaColors.metalTop));
	gradient.setColorAt(1., Color(activeWindow
		? st::aquaColors.selectionBottom : st::aquaColors.metalBottom));
	p.fillRect(rect, gradient);
	p.fillRect(QRect(rect.left(), rect.y() + rect.height() - st::aquaMetrics.line,
		rect.width(), st::aquaMetrics.line), Color(activeWindow
		? st::aquaColors.selectionBorder : st::aquaColors.panelBorder));
	p.restore();
}

void PaintPresence(QPainter &p, QPoint position, Presence presence) {
	const auto &c = st::aquaColors;
	const auto color = Color(presence == Presence::Available ? c.available
		: presence == Presence::Idle ? c.idle
		: presence == Presence::Away ? c.away
		: presence == Presence::Busy ? c.busy : c.offline);
	const auto &m = st::aquaMetrics;
	const auto rect = QRectF(position, QSize(m.presenceDiameter, m.presenceDiameter));
	p.save();
	p.setRenderHint(QPainter::Antialiasing);
	auto gradient = QLinearGradient(rect.topLeft(), rect.bottomLeft());
	gradient.setColorAt(0., color.lighter());
	gradient.setColorAt(1., color.darker());
	p.setPen(Qt::NoPen);
	p.setBrush(WithOpacity(color.darker(), m.focusOpacity));
	p.drawEllipse(Inset(rect, m.line / 2.).translated(0, m.shadowOffset));
	p.setBrush(gradient);
	p.setPen(QPen(color.darker(), m.line));
	p.drawEllipse(Inset(rect, m.line / 2.));
	p.setBrush(WithOpacity(Color(c.highlight), 0.8));
	p.setPen(Qt::NoPen);
	p.drawEllipse(QRectF(rect.topLeft() + QPoint(m.line, m.line),
		QSize(m.presenceHighlight, m.presenceHighlight)));
	p.restore();
}

} // namespace Ui::Aqua
