#pragma once

#include <QtCore/QMargins>
#include <QtCore/QRect>
#include <QtCore/QString>
#include <QtGui/QColor>

class QPainter;
class QPalette;
class QWidget;

namespace style {
struct InputField;
struct RoundButton;
} // namespace style

namespace Ui::Aqua {

enum class Presence { Available, Idle, Away, Offline, Busy };

[[nodiscard]] QString ResolveFontFamily(const QString &requested);
[[nodiscard]] bool IsLight();
void ApplyPalette();
void WatchFocus(QWidget *widget);
void UpdateFieldPalette(QPalette &palette, const style::InputField &style);
[[nodiscard]] bool PaintButton(
	QPainter &p,
	QRect rect,
	const style::RoundButton &style,
	bool hovered,
	bool pressed,
	bool enabled,
	bool focused);
[[nodiscard]] QColor ButtonTextColor(
	const style::RoundButton &style,
	bool hovered,
	bool pressed,
	bool enabled);
[[nodiscard]] double ContentOpacity(bool enabled);
[[nodiscard]] QMargins FieldTextMargins(
	const style::InputField &style,
	bool aqua = IsLight());
[[nodiscard]] QMargins ApplyFieldTextMargins(
	QWidget *widget,
	const style::InputField &style,
	QMargins requested);
[[nodiscard]] QMargins RequestedFieldTextMargins(
	QWidget *widget,
	const style::InputField &style);
[[nodiscard]] bool PaintField(
	QPainter &p,
	QRect rect,
	const style::InputField &style,
	double error,
	double focus,
	bool enabled);
[[nodiscard]] bool PaintMetal(QPainter &p, QRect rect);
void PaintSelection(QPainter &p, QRect rect, bool activeWindow);
void PaintPresence(QPainter &p, QPoint position, Presence presence);

} // namespace Ui::Aqua
