# AquaGram Implementation Milestones

Implement AquaGram incrementally.

Do not attempt the entire redesign in one change.


## M0 — Baseline

Goal:

Prove the fork builds and runs as an isolated macOS Debug client.

Required:

- clean Debug build
- isolated local profile/data
- working login/startup
- no Aqua changes
- clean git state except justified bootstrap fixes

Exit condition:

`READY FOR AQUA UI WORK`


## M1 — Aqua Foundation

Goal:

Create the reusable visual language without structurally redesigning every screen.

Implement:

- AquaGram design tokens
- primary/secondary surfaces
- brushed-metal structural chrome
- Aqua blue selection colors
- panel borders/separators
- primary/secondary button visual language
- search-field visual language
- focus states
- presence-indicator primitives
- base typography adjustments where safe

Do not yet:

- rewrite message layout
- heavily restructure sidebar
- redesign every settings page

Acceptance:

- clearly visible Aqua identity
- still functionally Telegram
- reusable styles, not scattered hardcoded paint values


## M2 — Buddy List Sidebar

Goal:

Transform the main dialog list into an MSN/iChat-like buddy-list presentation.

Implement:

- current-user identity/status area
- compact Aqua search
- compact dialog rows
- buddy-like avatar/presence presentation
- Aqua selection
- folder/group headers with disclosure treatment
- unread/muted states

Preserve Telegram folders and dialog semantics.


## M3 — Conversation Header

Goal:

Transform the chat top bar into a Messenger-like desktop toolbar.

Implement:

- avatar
- name
- presence/last seen
- Aqua structural chrome
- Call/Video/Search/Info action treatment
- compact toolbar icon language

Preserve all required Telegram actions.


## M4 — Conversation Log

Goal:

Remove ordinary Telegram bubble presentation for regular text messages.

Implement:

- `Name says: (time)` sender heading
- bubbleless text body
- speaker-turn grouping
- group-chat sender identity
- link/style compatibility
- selection/copy behavior
- timestamps
- edited state

Do not break:

- replies
- forwards
- reactions
- media
- service messages


## M5 — Rich Message Objects

Goal:

Adapt modern Telegram message types to the Aqua visual language.

Implement:

- replies
- forwards
- files
- photos
- video
- voice
- polls
- stickers/GIFs
- reactions
- bot keyboard
- service messages

Use framed Aqua content objects where needed.


## M6 — Composer

Goal:

Create an MSN-like desktop composer.

Implement:

- compact toolbar-like action row
- Aqua text area
- Attach / Send File presentation
- emoji/emoticon affordance
- formatting affordance
- visible Aqua Send button
- focus/default state

Preserve keyboard behavior and Telegram send semantics.


## M7 — Info / Profile

Goal:

Make the profile/info sidebar resemble a Tiger-era inspector/contact panel.

Implement:

- avatar/name/status hierarchy
- username
- notifications
- shared media
- files
- links
- groups/common info
- Aqua form rows and separators


## M8 — Preferences

Goal:

Apply Aqua/Tiger-era treatment to core settings.

Prioritize:

- common buttons
- checkbox/radio
- dropdown/selectors
- section headers
- text fields
- preferences navigation

Do not attempt a total settings rewrite unless necessary.


## M9 — Menus, Popovers, Polish

Implement:

- context menus
- small popovers
- scrollbars where feasible
- hover/pressed states
- progress controls
- loading indicators
- edge cases
- high-DPI polish
- non-100% UI scaling
- visual consistency audit


## M10 — Release Readiness

Verify:

- upstream rebase strategy
- build reproducibility
- no tracked credentials
- no unnecessary core changes
- accessibility
- keyboard navigation
- localization
- RTL behavior where supported
- crash-free common messaging flow
- screenshot acceptance set
