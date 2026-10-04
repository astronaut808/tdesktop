# AquaGram Visual Acceptance Criteria

Every major visual milestone must be evaluated using screenshots.

Do not approve a milestone solely because it compiles.


## 1. Required viewport checks

Evaluate at minimum:

- 1280×800
- 1440×900
- Retina/high-DPI backing scale
- at least one non-100% Telegram UI scale where practical


## 2. Golden scenario A — Simple private chat

Sidebar populated with multiple dialogs.

Selected private conversation.

Conversation contains:

- short incoming text
- multiline incoming text
- short outgoing text
- link
- several consecutive messages

Expected:

- ordinary messages are not Telegram bubbles
- sender identity is immediately clear
- conversation resembles a desktop conversation log
- spacing is compact but readable
- selected dialog looks Aqua-native


## 3. Golden scenario B — Rich private chat

Conversation includes:

- reply
- forwarded message
- image
- file
- voice message
- reaction

Expected:

- Telegram functionality remains
- rich objects use Aqua-style framed presentation
- ordinary text remains bubbleless
- metadata is compact and readable


## 4. Golden scenario C — Group chat

At least five senders.

Expected:

- every sender is clearly identifiable
- no ambiguity caused by removal of bubbles
- sender headings do not become excessively repetitive
- replies and mentions remain discoverable


## 5. Golden scenario D — Sidebar states

Capture:

- normal row
- hovered row
- selected row
- unread row
- muted row
- folder/group expanded
- folder/group collapsed
- search focused

Expected:

- all states are visually distinct
- selected row uses Aqua blue
- unread is not confused with selected
- rows remain compact


## 6. Golden scenario E — Composer

Capture:

- empty composer
- focused composer
- multiline text
- attachment state
- emoji/emoticon popup if changed
- send button default state
- send button pressed/hover state if changed

Expected:

- composer resembles a desktop text area + toolbar
- no oversized modern pill
- Send is a visible control


## 7. Golden scenario F — Profile/info

Capture right-side information panel.

Expected:

- resembles a Mac inspector/contact-information panel
- compact hierarchy
- not a mobile settings card stack


## 8. Golden scenario G — Settings

Capture one settings page containing:

- button
- checkbox
- text field
- dropdown or comparable selector
- section separator

Expected:

- controls look Aqua-inspired
- density is desktop-like
- keyboard focus remains obvious


## 9. Visual review questions

For every milestone screenshot answer:

1. Does this look like an application that plausibly shipped for Mac OS X Tiger?
2. Would a user mistake this for merely a Telegram custom theme?
3. Are controls visibly tactile?
4. Is information density desktop-like?
5. Are there modern oversized radii?
6. Are there floating cards where none are needed?
7. Is brushed metal subtle rather than noisy?
8. Does Aqua blue behave as an accent rather than covering everything?
9. Are Telegram actions still discoverable?
10. Is text/content more important than decoration?
11. Does the UI remain coherent at high DPI?
12. Did any historical styling reduce accessibility?


## 10. Automatic failure conditions

A milestone fails visual acceptance if the result can reasonably be described as:

- current Telegram with blue gradients
- current Telegram with retro icons
- current Telegram with a wallpaper
- modern macOS with old-looking icons
- generic Y2K UI
- Frutiger Aero
- Liquid Glass
- generic glassmorphism

Structural presentation must change where specified.


## 11. Code acceptance

Before accepting UI changes:

- Debug build succeeds
- no Release build is required
- `git diff` contains no generated build products
- no API credentials are tracked
- dimensions are defined through `.style` where appropriate
- no unnecessary core/network/storage changes are introduced
- existing Telegram actions remain functional
- changes are reasonably rebaseable against upstream


## 12. Screenshot rule

For visual milestones, coding agents should provide:

- at least one screenshot of the affected area
- a short comparison against this specification
- known deviations
- functional regression notes

Compilation success alone is not sufficient evidence.
