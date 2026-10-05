/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#include "tests/test_main.h"

#include "ui/aquagram/aquagram.h"
#include "ui/style/style_core.h"
#include "ui/style/style_core_palette.h"
#include "ui/widgets/fields/input_field.h"
#include "ui/widgets/fields/masked_input_field.h"
#include "ui/widgets/buttons.h"
#include "ui/rp_widget.h"

#include <QtCore/QTimer>
#include <QtCore/qmath.h>
#include <QtGui/QImage>
#include <QtGui/QFontDatabase>
#include <QtGui/QFontInfo>
#include <QtGui/QPainter>
#include <QtGui/QPalette>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

#include "styles/style_aquagram.h"
#include "styles/style_widgets.h"

namespace Test {
namespace {

[[nodiscard]] QColor Color(const QString &value) {
	return QColor(value);
}

void SetWindowBackground(const QColor &color) {
	const auto result = style::main_palette::setColor(
		QLatin1String("windowBg"),
		color.red(), color.green(), color.blue(), color.alpha());
	Expects(result == style::palette::SetResult::Ok
		|| result == style::palette::SetResult::Duplicate);
	style::NotifyPaletteChanged();
}

class MaskedField final : public Ui::MaskedInputField {
public:
	using MaskedInputField::MaskedInputField;
	void setPrefixMargins(QMargins margins);

};

class Surface final : public QWidget {
public:
	enum class Material { Metal, Content, Sidebar };

	Surface(QWidget *parent, Material material);

protected:
	void paintEvent(QPaintEvent *) override;

private:
	Material _material;

};

void MaskedField::setPrefixMargins(QMargins margins) {
	setTextMargins(margins);
}

Surface::Surface(QWidget *parent, Material material)
: QWidget(parent)
, _material(material) {
	setAttribute(Qt::WA_OpaquePaintEvent);
}

void Surface::paintEvent(QPaintEvent *) {
	auto p = QPainter(this);
	if (_material == Material::Metal) {
		if (!Ui::Aqua::PaintMetal(p, rect())) {
			p.fillRect(rect(), palette().window());
		}
		return;
	}
	p.fillRect(rect(), Color(_material == Material::Content
		? st::aquaColors.contentPrimary
		: st::aquaColors.sidebarTint));
	if (_material == Material::Sidebar) {
		const auto row = QRect(
			scale(8),
			scale(72),
			width() - scale(16),
			scale(42));
		Ui::Aqua::PaintSelection(p, row, true);
		Ui::Aqua::PaintPresence(
			p,
			QPoint(scale(18), scale(88)),
			Ui::Aqua::Presence::Available);
		Ui::Aqua::PaintPresence(
			p,
			QPoint(scale(18), scale(132)),
			Ui::Aqua::Presence::Away);
	}
}

[[nodiscard]] QImage PaintFieldSnapshot(const QColor &background) {
	const auto size = QSize(scale(96), scale(34));
	auto image = QImage(size, QImage::Format_ARGB32_Premultiplied);
	image.fill(background);
	auto p = QPainter(&image);
	Expects(Ui::Aqua::PaintField(
		p,
		QRect(QPoint(), size),
		st::aquaSearchField,
		0.,
		0.,
		true));
	return image;
}

void CheckPainterPrimitives() {
	const auto parent = Color(st::aquaColors.sidebarTint);
	const auto lightMargins = Ui::Aqua::FieldTextMargins(
		st::aquaSearchField,
		true);
	const auto darkMargins = Ui::Aqua::FieldTextMargins(
		st::aquaSearchField,
		false);
	Expects(lightMargins.left() >= darkMargins.left());
	Expects(lightMargins.right() >= darkMargins.right());
	const auto rounded = PaintFieldSnapshot(parent);
	// Rounded fields must leave the underlying material visible at their corners.
	Expects(rounded.pixelColor(0, 0) == parent);

	auto image = QImage(
		QSize(scale(64), scale(32)), QImage::Format_ARGB32_Premultiplied);
	image.fill(parent);
	auto p = QPainter(&image);
	const auto pen = QPen(Color(st::aquaColors.error), scale(1));
	p.setPen(pen);
	p.setBrush(Color(st::aquaColors.contentSecondary));
	p.setOpacity(0.75);
	Ui::Aqua::PaintSelection(p, image.rect(), true);
	Expects(p.pen() == pen);
	Expects(p.brush().color() == Color(st::aquaColors.contentSecondary));
	Expects(qFuzzyCompare(p.opacity(), 0.75));

	const auto original = st::windowBg->c;
	const auto dark = Color(st::aquaColors.blueDark);
	SetWindowBackground(dark);
	Expects(Ui::Aqua::FieldTextMargins(st::aquaSearchField) == darkMargins);
	const auto untouched = QImage(image);
	Expects(!Ui::Aqua::PaintField(
		p,
		image.rect(),
		st::aquaSearchField,
		0.,
		0.,
		true));
	Expects(image == untouched);
	Expects(!Ui::Aqua::PaintMetal(p, image.rect()));
	Expects(image == untouched);
	SetWindowBackground(original);
	Expects(Ui::Aqua::FieldTextMargins(st::aquaSearchField) == lightMargins);
}

void CheckMaskedPaletteCycle(
		not_null<Ui::MaskedInputField*> field,
		QMargins requested) {
	const auto original = st::windowBg->c;
	const auto dark = Color(st::aquaColors.blueDark);
	const auto lightTextMargins = field->textMargins();
	const auto lightContentsMargins = field->contentsMargins();
	SetWindowBackground(dark);
	const auto darkTextMargins = field->textMargins();
	const auto darkContentsMargins = field->contentsMargins();
	Expects(darkContentsMargins == requested + QMargins(-2, -1, -2, -1));
	SetWindowBackground(original);
	Expects(field->textMargins() == lightTextMargins);
	Expects(field->contentsMargins() == lightContentsMargins);
	SetWindowBackground(dark);
	Expects(field->textMargins() == darkTextMargins);
	Expects(field->contentsMargins() == darkContentsMargins);
	SetWindowBackground(original);
	Expects(field->textMargins() == lightTextMargins);
	Expects(field->contentsMargins() == lightContentsMargins);
}

void Place(QWidget *widget, int x, int y, int width, int height) {
	widget->setGeometry(scale(x), scale(y), scale(width), scale(height));
	widget->show();
}

void CheckLocalFieldStyles() {
	Expects(Ui::Aqua::IsLight());
	const auto dark = style::owned_color(Color(st::aquaColors.blueDark));
	const auto white = style::owned_color(Color(st::aquaColors.highlight));
	const auto transparent = style::owned_color(QColor(Qt::transparent));
	for (const auto background : { transparent.color(), dark.color() }) {
		auto fieldStyle = st::defaultInputField;
		fieldStyle.textBg = background;
		fieldStyle.textFg = white.color();
		fieldStyle.textMargins = QMargins(scale(2), scale(7), scale(2), 0);
		fieldStyle.placeholderScale = 0.;
		Expects(Ui::Aqua::FieldTextMargins(fieldStyle) == fieldStyle.textMargins);
		auto untouched = QImage(QSize(scale(96), scale(34)),
			QImage::Format_ARGB32_Premultiplied);
		untouched.fill(dark.color()->c);
		auto image = untouched;
		auto painter = QPainter(&image);
		Expects(!Ui::Aqua::PaintField(painter, image.rect(), fieldStyle,
			0., 1., true));
		painter.end();
		Expects(image == untouched);
		auto activeStyle = fieldStyle;
		activeStyle.textBg = st::windowBg;
		activeStyle.textBgActive = background;
		Expects(Ui::Aqua::FieldTextMargins(activeStyle) == activeStyle.textMargins);
		painter.begin(&image);
		Expects(!Ui::Aqua::PaintField(painter, image.rect(), activeStyle,
			0., 1., true));
		painter.end();
		Expects(image == untouched);
		auto palette = QPalette();
		palette.setColor(QPalette::Window, dark.color()->c);
		palette.setColor(QPalette::Disabled, QPalette::Text, white.color()->c);
		Ui::Aqua::UpdateFieldPalette(palette, fieldStyle);
		Expects(palette.color(QPalette::Disabled, QPalette::Text) == white.color()->c);
		Ui::Aqua::UpdateFieldPalette(palette, activeStyle);
		Expects(palette.color(QPalette::Disabled, QPalette::Text) == white.color()->c);
		auto host = QWidget();
		host.setPalette(palette);
		host.setAutoFillBackground(true);
		host.resize(scale(320), scale(140));
		auto field = Ui::InputField(&host, fieldStyle, rpl::single(QString()));
		auto masked = MaskedField(&host, fieldStyle, rpl::single(QString()));
		Place(&field, 0, 0, 300, 60);
		Place(&masked, 0, 70, 300, 60);
		field.setText(u"Local dark field"_q);
		masked.setText(u"Local dark field"_q);
		Expects(masked.contentsMargins()
			== fieldStyle.textMargins + QMargins(-2, -1, -2, -1));
		Expects(field.rawTextEdit()->palette().color(QPalette::Text)
			== white.color()->c);
		Expects(masked.palette().color(QPalette::Text) == white.color()->c);
		for (const auto widget : { static_cast<QWidget*>(&field),
				static_cast<QWidget*>(&masked) }) {
			const auto snapshot = widget->grab().toImage();
			const auto sample = snapshot.pixelColor(
				snapshot.width() - scale(20), snapshot.height() / 2);
			Expects(sample.lightnessF() < st::aquaMetrics.lightThreshold);
		}
		const auto renderPath = qEnvironmentVariable("AQUAGRAM_LOCAL_FIELD_RENDER_PATH");
		if (!renderPath.isEmpty()) {
			const auto suffix = background->c.alpha() ? u"-dark.png"_q
				: u"-transparent.png"_q;
			Expects(host.grab().save(renderPath + suffix, "PNG"));
		}
	}
}

void CheckButtonStates(not_null<Ui::RoundButton*> button) {
	const auto normal = button->grab().toImage();
	button->setSynteticOver(true);
	const auto hovered = button->grab().toImage();
	Expects(hovered != normal);
	auto clicks = 0;
	button->setClickedCallback([&] { ++clicks; });
	button->setSynteticDown(true);
	const auto pressed = button->grab().toImage();
	Expects(pressed != hovered);
	Expects(clicks == 0);
	button->setSynteticDown(false);
	Expects(clicks == 1);
	button->setClickedCallback({});
	button->setSynteticOver(false);
	button->setDisabled(true);
	Expects(button->grab().toImage() != normal);
	button->setDisabled(false);
	Expects(button->grab().toImage() == normal);
	button->setEnabled(false);
	Expects(button->grab().toImage() != normal);
	button->setEnabled(true);
	Expects(button->grab().toImage() == normal);
}

} // namespace

QString name() {
	return u"aquagram"_q;
}

void test(not_null<Ui::RpWindow*>, not_null<Ui::RpWidget*> body) {
	Expects(Ui::Aqua::ResolveFontFamily(u"User font"_q) == u"User font"_q);
	Expects(Ui::Aqua::ResolveFontFamily(style::SystemFontTag())
		== style::SystemFontTag());
	const auto family = Ui::Aqua::ResolveFontFamily(QString());
#ifdef Q_OS_MAC
	if (QFontDatabase::families().contains(u"Lucida Grande"_q)) {
		Expects(family == u"Lucida Grande"_q);
		const auto font = style::font(scale(13), {}, family);
		Expects(QFontInfo(font->f).family() == family);
		Expects(font->height < st::aquaPushButton.height);
	}
#else // Q_OS_MAC
	Expects(family.isEmpty());
#endif // Q_OS_MAC
	CheckPainterPrimitives();
	CheckLocalFieldStyles();

	const auto metal = new Surface(body, Surface::Material::Metal);
	Place(metal, 0, 0, 800, 64);
	const auto sidebar = new Surface(body, Surface::Material::Sidebar);
	Place(sidebar, 0, 64, 224, 536);
	const auto content = new Surface(body, Surface::Material::Content);
	Place(content, 224, 64, 576, 536);

	const auto primary = new Ui::RoundButton(
		metal, rpl::single(u"Default"_q), st::aquaPrimaryButton);
	Place(primary, 18, 16, 112, 32);
	const auto primarySnapshot = primary->grab().toImage();
	Expects(!primarySnapshot.isNull());
	Expects(primarySnapshot.deviceIndependentSize() == primary->size());
	CheckButtonStates(primary);

	const auto silver = new Ui::RoundButton(
		metal, rpl::single(u"Silver"_q), st::aquaPushButton);
	Place(silver, 142, 16, 104, 32);
	const auto disabled = new Ui::RoundButton(
		metal, rpl::single(u"Disabled"_q), st::aquaPrimaryButton);
	Place(disabled, 258, 16, 112, 32);
	disabled->setDisabled(true);
	const auto hovered = new Ui::RoundButton(
		metal, rpl::single(u"Hover"_q), st::aquaPrimaryButton);
	Place(hovered, 382, 16, 104, 32);
	hovered->setSynteticOver(true);
	const auto pressed = new Ui::RoundButton(
		metal, rpl::single(u"Pressed"_q), st::aquaPrimaryButton);
	Place(pressed, 498, 16, 104, 32);
	pressed->setSynteticOver(true);
	pressed->setSynteticDown(true);

	const auto search = new Ui::InputField(
		sidebar, st::aquaSearchField, rpl::single(u"Search"_q));
	Place(search, 16, 22, 192, 30);
	const auto focused = new Ui::InputField(
		content, st::aquaSearchField, rpl::single(u"Focused field"_q));
	Place(focused, 28, 36, 260, 30);
	focused->setFocus();
	const auto error = new Ui::MaskedInputField(
		content, st::aquaSearchField, rpl::single(u"Error field"_q));
	Place(error, 28, 86, 260, 30);
	error->showErrorNoFocus();
	const auto masked = new MaskedField(
		content, st::defaultInputField, rpl::single(u"Masked input"_q));
	Place(masked, 28, 136, 260, 60);
	masked->setText(u"0123"_q);
	CheckMaskedPaletteCycle(masked, st::defaultInputField.textMargins);
	const auto prefixMargins = QMargins(scale(24), scale(28), 0, scale(4));
	masked->setPrefixMargins(prefixMargins);
	CheckMaskedPaletteCycle(masked, prefixMargins);

	const auto custom = new Ui::RoundButton(
		content, rpl::single(u"Full-radius override"_q), st::aquaPrimaryButton);
	Place(custom, 28, 220, 220, 32);
	custom->setFullRadius(true);
	custom->setRippleOverride(Color(st::aquaColors.focus));

	const auto renderPath = qEnvironmentVariable("AQUAGRAM_RENDER_PATH");
	if (!renderPath.isEmpty() || qEnvironmentVariableIsSet("AQUAGRAM_SELF_TEST")) {
		QTimer::singleShot(renderPath.isEmpty() ? 0 : 250, body, [=] {
			if (!renderPath.isEmpty()) {
				Expects(body->grab().save(renderPath, "PNG"));
			}
			QCoreApplication::quit();
		});
	}
}

} // namespace Test
