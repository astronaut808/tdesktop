import hashlib
from pathlib import Path
import sys


def replace_once(text, before, after, name):
    if text.count(before) != 1:
        raise RuntimeError(f'AquaGram hook drift in {name}: expected one anchor')
    return text.replace(before, after)


def transform(name, text):
    text = text.replace("\r\n", "\n")
    first_include = text.index('#include ')
    end_include = text.index('\n', first_include)
    text = text[:end_include] + '\n\n#include "ui/aquagram/aquagram.h"' + text[end_include:]
    if name == 'ui/style/style_core.cpp':
        text = replace_once(text, '\tinternal::StartModules(scale);',
            '\tinternal::StartModules(scale);\n\tUi::Aqua::ApplyPalette();', name)
        text = replace_once(text, 'void NotifyPaletteChanged() {',
            'void NotifyPaletteChanged() {\n\tUi::Aqua::ApplyPalette();', name)
    elif name == 'ui/widgets/buttons.cpp':
        text = replace_once(text, ', _fullRadius(st.fullRadius) {',
            ', _fullRadius(st.fullRadius) {\n\tAqua::WatchFocus(this);', name)
        before = '''\tdrawRect(_roundRect);

\tauto over = isOver();
\tauto down = isDown();
\tif (!_brushOverride && (over || down)) {
\t\tdrawRect(_roundRectOver);
\t}'''
        after = '''\tauto over = isOver();
\tauto down = isDown();
\tconst auto enabled = isEnabled() && !isDisabled();
\tconst auto aqua = !_brushOverride
\t\t&& !_penOverride
\t\t&& !_cornerRadii
\t\t&& !_fullRadius
\t\t&& !_rippleOverride
\t\t&& Aqua::PaintButton(
\t\t\tp,
\t\t\tmyrtlrect(rounded),
\t\t\t_st,
\t\t\tover,
\t\t\tdown,
\t\t\tenabled,
\t\t\thasFocus());
\tif (!aqua) {
\t\tdrawRect(_roundRect);
\t\tif (!_brushOverride && (over || down)) {
\t\t\tdrawRect(_roundRectOver);
\t\t}
\t}'''
        text = replace_once(text, before, after, name)
        text = replace_once(text, '\tif (!_penOverride || _rippleOverride) {',
            '\tif (!aqua && (!_penOverride || _rippleOverride)) {', name)
        text = replace_once(text, '\tconst auto textTop = _st.padding.top() + _st.textTop;',
            '\tif (aqua) {\n\t\tp.setOpacity(Aqua::ContentOpacity(enabled));\n\t}\n\tconst auto textTop = _st.padding.top() + _st.textTop;', name)
        text = replace_once(text, '\t\t\tp.setPen((over || down) ? _st.textFgOver : _st.textFg);',
            '\t\t\tp.setPen(aqua\n\t\t\t\t? Aqua::ButtonTextColor(_st, over, down, enabled)\n\t\t\t\t: ((over || down) ? _st.textFgOver : _st.textFg)->c);', name)
    elif name == 'ui/widgets/fields/input_field.cpp':
        text = replace_once(text, '\tif (_st.borderRadius > 0) {\n\t\tpaintRoundSurrounding',
            '''\tif (Aqua::PaintField(p, rect(), _st, errorDegree, focusedDegree,
\t\tisEnabled())) {
\t\treturn;
\t}
\tif (_st.borderRadius > 0) {
\t\tpaintRoundSurrounding''', name)
        text = text.replace('_st.textMargins', 'Aqua::FieldTextMargins(_st)')
        text = replace_once(text,
            '\t\tupdatePalette();\n\t}, lifetime());',
            '\t\tupdatePalette();\n\t\tQResizeEvent event(size(), size());\n\t\tresizeEvent(&event);\n\t}, lifetime());', name)
    elif name == 'ui/widgets/fields/masked_input_field.cpp':
        text = replace_once(text, '\t_textMargins = mrg;',
            '\t_textMargins = Aqua::ApplyFieldTextMargins(this, _st, mrg);', name)
        text = replace_once(text,
            ') | rpl::on_next([=] {\n\t\tupdatePalette();\n\t}, lifetime());',
            ''') | rpl::on_next([=] {
\t\tupdatePalette();
\t\tsetTextMargins(Aqua::RequestedFieldTextMargins(this, _st));
\t}, lifetime());''', name)
        before = '''\tp.fillRect(r, _st.textBg);
\tif (_st.border) {
\t\tp.fillRect(0, height() - _st.border, width(), _st.border, _st.borderFg->b);
\t}'''
        after = '''\tconst auto aqua = Aqua::PaintField(
\t\tp,
\t\trect(),
\t\t_st,
\t\t_a_error.value(_error ? 1. : 0.),
\t\t_a_focused.value(_focused ? 1. : 0.),
\t\tisEnabled());
\tif (!aqua) {
\t\tp.fillRect(r, _st.textBg);
\t\tif (_st.border) {
\t\t\tp.fillRect(0, height() - _st.border, width(), _st.border, _st.borderFg->b);
\t\t}
\t}'''
        text = replace_once(text, before, after, name)
        text = replace_once(text, '\tif (_st.borderActive && (borderOpacity > 0.)) {',
            '\tif (!aqua && _st.borderActive && (borderOpacity > 0.)) {', name)
    else:
        raise RuntimeError(f'Unknown AquaGram overlay: {name}')
    if name in ('ui/widgets/fields/input_field.cpp', 'ui/widgets/fields/masked_input_field.cpp'):
        text = replace_once(text,
            '\tp.setColor(QPalette::HighlightedText, st::historyTextInFgSelected->c);',
            '\tp.setColor(QPalette::HighlightedText, st::historyTextInFgSelected->c);\n\tAqua::UpdateFieldPalette(p);', name)
    return text


def main():
    source, output = map(Path, sys.argv[1:])
    for name, expected in PINS.items():
        original = (source / name).read_bytes().replace(b"\r\n", b"\n")
        if hashlib.sha256(original).hexdigest() != expected:
            raise RuntimeError(f'AquaGram overlay input changed: {name}; review hooks before updating pin')
        result = transform(name, original.decode()).encode()
        target = output / name
        target.parent.mkdir(parents=True, exist_ok=True)
        if not target.exists() or target.read_bytes() != result:
            target.write_bytes(result)


PINS = {
    'ui/style/style_core.cpp': '5a6f861db2c1070267a00500e18e9f80c6ccf52dbe813da2a94173d0c18a1b23',
    'ui/widgets/buttons.cpp': '8cead5748e8a1bbfdd0bfbf51dc7d759aa2c257e34ea9d58e7080f1fffdbebfc',
    'ui/widgets/fields/input_field.cpp': '8fa68badede170d52a2ff1e5b96a0eb3527007dcbe8a8bd18d5ca630127db00f',
    'ui/widgets/fields/masked_input_field.cpp': '90480382510a6f511caef73b068a8075c855e3a24bc05d07e4e42bd4328057ce',
}

if __name__ == '__main__':
    main()
