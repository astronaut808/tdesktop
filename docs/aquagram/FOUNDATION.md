# M1 Aqua foundation implementation

M1 supplies shared visual primitives. It preserves dialog-row geometry, message
bubbles and grouping, composer layout, command sets, and all protocol/storage
semantics. The later structural milestones remain outstanding.

## Tokens and painting

`Telegram/SourceFiles/ui/aquagram/aquagram.style` owns:

- `aquaColors`: bright content, blue-gray sidebar, metal, panel/separator,
  silver/blue/pressed/disabled controls, focus/error, and presence colors;
- `aquaMetrics`: scalable border/focus widths, inset/radii, field padding,
  grain pitch, jewel diameter/highlight, and material opacity/gradient stops;
- `aquaControlText`, `aquaPushButton`, `aquaPrimaryButton`, `aquaSearchField`,
  `aquaPrefixedField`, `aquaLinkField`:
  compact shared control styles.

Unique color literals are permitted only in the toolkit's palette module by
Telegram's generator. To keep that pinned submodule unchanged, original Aqua
colors are named string tokens in the application `.style` module, converted to
`QColor` at the palette/painting boundary. No color literals or scalable
geometry are embedded in the Aqua C++ painter.

`ui/aquagram/aquagram.cpp` centralizes tactile silver/default blue push-button
bodies, inset fields, focus rings, restrained brushed metal, active/inactive
selection and jewel presence primitives. Existing button text, icons, numbers,
accessibility, click handling and field editor/placeholder/error logic continue
to be rendered by the toolkit. Explicit custom brushes/pens/corner-radii/ripples,
full-radius controls and
small badge buttons retain their existing painting. Touching focus or enabled
state schedules a repaint; the observer does not consume input events.

The primary style identifies an existing primary action; no default action is
inferred from its label. HIG pulsing is not implemented in M1. Presence painting
is a reusable primitive only; it does not invent or map Telegram presence data.

Every light palette receives the Aqua foundation tokens through Telegram's
palette API, including imported light themes. This is the fork's intentional
visual policy; it does not preserve those themes' original foundation colors.
Dark palettes retain upstream painting and automatic field geometry. Explicit
Aqua control styles retain their specified dimensions in either palette.
Fields with explicitly transparent or locally dark backgrounds retain their
upstream surrounding, margins and disabled-text palette even when the main
application palette is light. A shared eligibility check covers both field
classes and all three adaptation points; this preserves white text in dark call
and story forms without inventing per-screen exceptions.
Palette changes
refresh field geometry, including cached masked-field margins. M1 defines the
requested bright Aqua appearance, not a historical dark-mode variant. Custom
wallpaper/theme identities are preserved; the built-in Classic light conversation
background becomes a bright content surface. Header and sidebar structural bars share the metal
painter. Rounded fields preserve their parent's material outside the capsule.
Dialog selection uses the owning window's active state and repaints when it
changes; painting changes material, not row composition.

Fixed URL and bot username prefixes share a five-pixel styled inset with their
editor. Bot prefix/suffix reservations include this base margin; their labels
remain inside the field border. These explicit form styles also use the inset
in dark palettes. No credentials, bot creation behavior or requests are changed.

## Toolkit integration

There is no public global painter hook in the pinned `Telegram/lib_ui` controls.
`Telegram/cmake/aquagram.cmake` therefore compiles four adapted translation units
under the ignored build directory, leaving the submodule and its public headers
unchanged. `aquagram_overlay.py` checks normalized content hashes and unique
anchors, failing configuration on upstream drift instead of silently applying a
partial adaptation. The adapter changes only button background/focus, field
surrounding/padding, and palette notification/startup seams.

Aqua code and its generated style module compile into `lib_ui`, making the
adapted toolkit self-contained for toolkit-only test applications. Style codegen
is a separate dependency shared with the application styles. Nothing generated
under `out/` belongs in a source commit.

The adapter's focused checks include actual pinned inputs, missing/duplicate
anchors, changed upstream rejection, and CRLF checkout equivalence. After an
upstream toolkit rebase, review these four seams before updating the pins.

## Historical references

The sibling `aqua-hig-reference` checkout is reference material, not application
assets. The September 2005 Apple HIG sections consulted were Keyboard Focus and
Navigation (pp. 99–100), Push Buttons (pp. 222–224), Text Input Fields
(pp. 256–257), Search Fields (p. 259), and Brushed Metal Windows (pp. 180–181).
The button/default-button, focus-ring and iSync metal illustrations were viewed.
They informed original vector painting; no artwork or proprietary fonts was copied.

References:

- [Apple HIG historical archive](https://github.com/johnzfitch/human-interface-markdown/tree/master/2005-09-apple-human-interface-guidelines)
- [Microsoft Messenger for Mac 5.0 release description](https://www.mactech.com/2005/08/09/messenger-for-mac-5-0/)
- [Tiger screenshot library](https://512pixels.net/projects/aqua-screenshot-library/mac-os-x-10-4-tiger/)

Control heights are adapted to current Telegram localization and scaling rather
than literal 20-pixel historical push-button geometry. On macOS, an empty font
preference resolves to Lucida Grande only when the host already provides that
family. Explicit user choices, including the system-font option, remain intact;
other hosts or an unavailable family retain the upstream fallback. The existing
font resolver continues to normalize metrics and handle script fallback. No font
assets are bundled or copied. Existing application icons are retained.

## Screenshot review and limits

The Tiger library's iChat AV buddy-list/preferences illustration was actually
viewed, as well as the HIG illustrations above. Messenger 5.0's release account
was consulted for its brushed-metal direction; a verified Messenger 5.0 control
screenshot was not obtained. It is not substituted with a later Windows or
Messenger 8 screenshot.

Local review images live outside this checkout in `../AquagramM1Review/` and
are not committed because authenticated views contain personal chat data:

- `m1-main-after-restart-retina.jpg`: authenticated Saved Messages, normal,
  selected and unread rows, shared header/search metal, bright conversation;
- `m1-main-expanded-retina.jpg`, `m1-selection-inactive-retina.jpg`: expanded
  main window and the owning window's inactive gray selection;
- `m1-main-lucida-retina.jpg`, `m1-buttons-lucida-retina.jpg`,
  `m1-fields-lucida-retina.jpg`: latest Debug after the native-font change,
  with the authenticated main window, shared buttons and focused form fields;
- `m1-main-after-local-field-fix-retina.jpg`: authenticated main window after
  the local-field compatibility correction; `m1-local-field-transparent.png`
  and `m1-local-field-dark.png` are actual two-field toolkit fixtures showing
  retained white text and transparent/dark backgrounds, not live call screens;
- `m1-search-focus-retina.jpg`, `m1-search-result-retina.jpg`: focused shared
  search and the result for the test message;
- `m1-main-multiline-retina.jpg`: multiline composer input;
- `m1-common-buttons-retina.jpg`, `m1-common-fields-retina.jpg`: real settings
  dialogs with silver buttons, inset form fields and field focus;
- `m1-phone-focus-retina.jpg`: earlier login form with the Aqua primary button.
- `m1-control-states-retina.png`: standalone toolkit fixture, not a main-window
  substitute; default/silver/disabled/hover/pressed controls, field focus/error,
  presence jewels and a retained full-radius override.

Captures retain the provider's original image bytes, without cropping or repainting.

Against DESIGN sections 5–8 and ACCEPTANCE's visual questions, the shared chrome
now has a restrained gray metal gradient, clearly separated bright content,
blue selection, inset field borders and tactile buttons. The first authenticated
render exposed excessive grain, a stock dark folder rail and a patterned default
background. Grain was reduced, the rail received structural palette tokens and
the default background identity guard was corrected before the next review.
Text remains readable on selected rows and field focus is visible at Retina
backing scale and 110% Telegram UI scale. The independent review confirmed
coherent M1 materials and controls across these actual screens.
The latest native-font pass preserves the distinction between ordinary and
bold text, secondary metadata and names. No vertical clipping was observed in
the reviewed main window or forms. Lucida Grande has denser strokes than Open
Sans, especially in Cyrillic, consistent with the historical font direction.

The full application still has Telegram dialog geometry, bubbles, composer
structure, stock icons, modern settings radio/checkbox shapes and platform
window chrome. They differ from the historical references and remain for their
assigned later milestones. M1 supplies their reusable foundation; the complete
Messenger-like structural presentation is not yet accepted. Button heights are
adapted to localization, default-button pulsing is absent, and presence jewels
are not yet wired to dialog data.

Validation observed sending two labelled test messages, multiline text/link
preview, editing and search in Saved Messages only, including persistence after
a clean restart. Existing photo/file/forwarded content rendered. No other peer
was messaged. Calls, bots, polls, voice, RTL and full accessibility coverage were
not functionally exercised; no exhaustive regression claim is made. Prefix
form fixes were reviewed in source but those two forms were not captured live.

Four Python overlay checks passed. The Debug toolkit harness checks rounded
field corners, painter state preservation, dark fallbacks, repeated masked-field
margin restoration, Retina snapshots and actual RoundButton state rendering.
It also verifies one action on release, both Telegram's internal disabled flag
and Qt's enabled state, and restoration after re-enabling. This caught and fixed
an initial overlay omission of Telegram's internal disabled flag.
An additional independent architecture audit identified that the first adapter
could whiten local dark fields under a global light palette. The regression
check now covers transparent and opaque dark styles with white text in actual
InputField and MaskedInputField controls, alongside preserved margins and
disabled palettes. Light normal backgrounds with dark/transparent active
backgrounds are also covered. Calls and stories are still not claimed as fully
tested live.

Exact 1280×800 and 1440×900 main-window captures remain outstanding. The
native automation could not resize the window; existing captures at other
sizes (880×724 and 1512×874 logical pixels, 2× backing scale) do not satisfy
or replace those viewport checks. On 2026-10-05 the user explicitly deferred
these two sizes to a later visual pass. They are recorded as follow-up work,
not as completed validation, and no longer block M1 publication. The other
M1 build, launch, visual review and source acceptance checks passed.

## Source manifest

- Foundation: `Telegram/SourceFiles/ui/aquagram/aquagram.style`,
  `aquagram.h`, `aquagram.cpp` in that directory.
- Default-font selection: `Telegram/SourceFiles/core/application.cpp`, using
  the shared Aqua font-family resolver before font initialization.
- Shared style consumers: `Telegram/SourceFiles/intro/intro.style`,
  `dialogs/dialogs.style`, `boxes/add_contact_box.style`,
  `boxes/peers/edit_peer_members.style`.
- Structural material/selection integration:
  `Telegram/SourceFiles/dialogs/dialogs_widget.cpp`,
  `dialogs/dialogs_inner_widget.cpp`, `dialogs/ui/dialogs_layout.cpp`,
  `dialogs/ui/dialogs_layout.h`, `history/view/history_view_top_bar_widget.cpp`,
  `window/section_widget.cpp`.
- Fixed-prefix presentation compatibility:
  `Telegram/SourceFiles/boxes/peers/create_managed_bot_box.cpp`.
- Build integration: `Telegram/CMakeLists.txt`, `Telegram/cmake/td_ui.cmake`,
  `Telegram/cmake/aquagram.cmake`, `Telegram/cmake/aquagram_overlay.py`,
  `Telegram/cmake/aquagram_tests.cmake`.
- Focused checks: `Telegram/cmake/tests/test_aquagram_overlay.py`,
  `Telegram/SourceFiles/tests/test_aquagram.cpp`.
- Implementation/review record: this document.

The toolkit submodule, credentials, isolated profile, launch helper, screenshots
and generated build output are not part of the source diff. The existing local
launch helper was corrected to use macOS application launching with explicit
isolated-profile arguments, preventing an unprofiled extra instance during
native UI inspection. Authentication survived the clean restart.
