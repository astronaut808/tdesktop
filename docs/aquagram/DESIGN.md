# AquaGram Visual Design Specification

## 1. Design target

AquaGram is not "Telegram with a blue theme".

The intended visual target is:

**Microsoft Messenger for Mac 5.x running on Mac OS X 10.4 Tiger, with visual influence from Mac OS X 10.3 Panther and iChat AV.**

Target period: **2003–2006**.

Primary aesthetic:

- classic Aqua
- brushed metal
- compact desktop UI
- visible controls
- tactile gradients and borders
- bright content panels
- early-2000s Mac density

The UI should look plausibly like an application designed by a Mac software team in 2005.

It must NOT look like:

- modern macOS
- iOS
- Big Sur / Sonoma / Tahoe
- Liquid Glass
- Windows Live Messenger for Windows
- Material Design
- generic glassmorphism
- a Telegram theme with different colors


## 2. Reference priority

When references conflict, use this priority:

### P0 — Microsoft Messenger for Mac 5.x
Determines messenger identity and conversation layout.

### P1 — Apple Human Interface Guidelines 2005
Determines controls, spacing philosophy, interaction hierarchy, window structure, Aqua conventions.

### P2 — Mac OS X 10.3 Panther / 10.4 Tiger
Determines surface materials, gradients, chrome, density and visual tone.

### P3 — iChat AV 2/3
Determines native Mac instant-messaging conventions.

### P4 — Telegram Desktop
Determines functionality only, not visual identity.

Modern macOS conventions may be used only where required for accessibility, Retina/high-DPI correctness, keyboard behavior, localization, RTL compatibility or current platform compatibility.


## 3. Visual character

The interface should feel:

- precise
- compact
- bright
- tactile
- desktop-native
- slightly playful
- early-2000s
- functional rather than decorative

Use visible UI chrome.

Controls are allowed to visibly look like controls.

Depth is expressed through:

- gradients
- 1 px borders
- inner highlights
- restrained shadows
- material transitions
- subtle specular highlights

Avoid:

- flat monochrome surfaces
- huge empty regions
- oversized cards
- oversized pills
- giant diffuse shadows
- translucent floating panels everywhere


## 4. Main window structure

Target layout:

```text
+--------------------------------------------------------------+
| title / unified application chrome                           |
+----------------------+---------------------------------------+
|                      | chat header                           |
| contact/dialog list  +---------------------------------------+
|                      |                                       |
|                      | conversation                          |
|                      |                                       |
|                      |                                       |
|                      +---------------------------------------+
|                      | composer toolbar                      |
|                      | composer                              |
+----------------------+---------------------------------------+
```

Preferred desktop-first proportions at 100% UI scale:

- sidebar target width: 260–310 px
- preferred initial sidebar width: 280 px
- conversation minimum useful width: ~500 px
- top conversation header: ~60–76 px
- dialog row: ~34–46 px
- buddy-group header: ~22–26 px
- composer total height: ~80–110 px

These are AquaGram design targets, not claims about historic Apple dimensions.

All implementation dimensions must live in `.style` files and scale using Telegram Desktop's style system.

Do not hardcode geometry in C++ where an appropriate style value can be used.


## 5. Materials

### 5.1 Brushed metal

Use brushed metal for structural chrome:

- primary toolbar/header
- bottom toolbar
- structural bars
- selected framed control surfaces where appropriate

Do not turn the entire UI into noisy metal.

The material should primarily read as a subtle vertical gray gradient with extremely restrained horizontal grain.

Suggested AquaGram tokens:

```text
metalTop        #ECEEEF
metalMiddle     #D6D9DB
metalBottom     #BEC3C6
metalBorder     #8E979D
metalHighlight  rgba(255,255,255,0.80)
```

Do not use photographic metal textures.

If grain is used, it must be subtle enough that text remains perfectly clean.


### 5.2 Content panels

Main content remains bright:

```text
contentPrimary     #FFFFFF
contentSecondary   #F4F8FB
sidebarTint        #EDF5FA
panelBorder        #B8C6D0
softSeparator      #D5DEE5
```

The interface should maintain strong separation between window chrome and content.


## 6. Aqua blue

The primary interactive color is classic Aqua blue, not Telegram blue.

Suggested project palette:

```text
aquaBlueLight       #7BC5FF
aquaBlue            #3198E8
aquaBlueDark        #1472C4

selectionTop        #73BDF5
selectionBottom     #338EDC
selectionBorder     #2476B8

focusBlue           #3A9BEC
linkBlue            #2368B0
```

These are AquaGram design tokens, not exact historical Apple color values.

Aqua blue is an accent.

Do not cover the whole application in blue.


## 7. Presence

Use compact jewel-like presence indicators.

Suggested colors:

```text
available   #62BD42
idle        #F0B932
away        #E15D4E
offline     #AEB7BE
busy        #D84C45
```

Presence indicators should have:

- thin darker outline
- subtle vertical gradient
- small specular highlight
- restrained shadow

They must look like small Aqua indicators, not flat CSS circles.

Telegram privacy semantics must remain truthful.

Do not fabricate exact presence information when Telegram does not provide it.


## 8. Geometry

AquaGram uses restrained rounding.

Recommended visual radii:

- small controls: 4–6 px
- Aqua push buttons: 5–8 px depending on height
- search field: capsule/pill geometry is historically appropriate
- internal application panels: mostly square or low-radius
- rich-message frames: 4–6 px

Avoid:

- 12–24 px modern card radii
- floating cards everywhere
- modern giant pills
- soft rounded rectangles for every object


## 9. Typography

Historical visual reference: Lucida Grande-era Mac OS X.

Do not bundle or redistribute proprietary fonts.

Prefer native/system fonts available on the host.

Reproduce the character of the period using:

- compact metrics
- moderate weights
- clear hierarchy
- small UI labels
- no giant modern headings

Suggested target sizes at 100% UI scale:

```text
UI labels                 11–12 px
dialog/contact names      12–13 px
secondary status          10–11 px
chat sender header        12–13 px semibold
chat message              13–14 px
conversation title        15–17 px
toolbar label             10–11 px
```

Exact values must be validated visually and stored in `.style`.


## 10. Icons

Icon style should approximate Mac OS X 10.3–10.4:

- pictorial
- dimensional
- glossy where appropriate
- blue/silver dominant
- clear metaphor
- usually 16–32 px UI size
- detailed enough to remain recognizable

Avoid modern outline-only icons as the primary toolbar language.

Do not directly copy copyrighted Apple or Microsoft assets.

Create original assets inspired by period conventions.


## 11. Sidebar

The Telegram dialog list becomes visually equivalent to an MSN/iChat Buddy List.

Sidebar hierarchy:

```text
current-user identity/status
search
folder/buddy-group header
dialog/contact rows
utility area where appropriate
```

Current-user identity area should visually contain:

- avatar
- display name
- presence/status
- optional short status text


### 11.1 Dialog/contact row

A dialog row should contain:

- presence indicator where meaningful
- avatar/buddy image
- display name
- secondary status/message preview
- unread state
- mute state when needed

Selected row:

- classic Aqua blue vertical gradient
- 1 px darker blue outline where visually useful
- strong readable text contrast
- compact height

Unread state must remain clearly distinct from selected state.


### 11.2 Groups/folders

Telegram folders/categories may visually resemble old buddy-list groups.

Group header:

- disclosure triangle
- small label
- optional count
- subtle blue-gray background or separator
- obvious collapsed/expanded state

Do not change Telegram folder semantics merely to imitate MSN.


## 12. Conversation header

The header should resemble the upper portion of a Messenger conversation window.

Left:

- avatar
- display name
- presence/last seen
- optional short status

Right:

- Call
- Video
- Search
- Info
- other existing Telegram actions where required

Actions should use pictorial Aqua-style toolbar icons.

Text labels may be used for the most important actions when there is enough width.

The header should feel like a desktop toolbar, not a mobile navigation bar.


## 13. Conversation rendering

This is one of the most important transformations.

Ordinary 1:1 text messages should not visually resemble Telegram bubbles.

Preferred text conversation:

```text
Chris says: (20:42)

Привет.
Как дела?


astronaut808 says: (20:43)

Нормально, работаю над новой версией.
```

Sender header:

- colored sender name
- time visually secondary
- compact typography
- no ordinary message bubble around text

Message body:

- white conversation background
- normal left-aligned text
- restrained indentation
- clear vertical separation between speaker turns

Multiple consecutive messages from the same author should remain readable without excessive repeated chrome.

Group chats must remain usable and clearly identify every sender.


## 14. Rich Telegram messages

Removing ordinary bubbles must not destroy Telegram semantics.

Special content may use framed Aqua-style content blocks:

- reply
- forwarded message
- photo
- album
- video
- file
- voice message
- poll
- location
- contact
- sticker
- GIF
- code block
- bot keyboard
- service message

Use:

- pale blue/gray panels
- subtle 1 px borders
- low corner radius
- compact metadata
- existing Telegram interaction affordances

Do not force every modern Telegram object into a literal 2005 MSN metaphor if doing so harms usability.


## 15. Replies

Replies should resemble inset quoted content rather than modern bubble-within-bubble UI.

Target:

- thin Aqua-blue vertical rule
- small sender name
- one or two lines of quoted text
- optional very pale blue background
- compact vertical spacing


## 16. Reactions

Reactions are modern Telegram functionality and must remain.

Style them as small compact Aqua controls.

They should feel integrated with the historical UI rather than like floating mobile pills.


## 17. Composer

The composer should feel explicitly toolbar-like.

Top mini-toolbar may contain:

- formatting/font
- emoji/emoticons
- attach / Send File
- other Telegram actions

Below:

- multi-line text input

Right:

- Send button

The Send button should look like a real Aqua default push button.

The text input should resemble a native Mac text area from the era, not an oversized rounded Telegram pill.


## 18. Search

Search fields should use classic rounded Mac search-field geometry.

Include:

- magnifying-glass affordance
- inset appearance
- subtle inner shadow
- clear focus state
- compact height

Avoid giant search bars.


## 19. Scrollbars

Prefer traditional Aqua-style scrollbars where technically reasonable.

They should remain visible enough to communicate scrollability.

Do not intentionally imitate current macOS auto-hidden minimalist scrollbars inside custom UI if the Telegram rendering architecture allows a controlled custom style.


## 20. Buttons

Buttons should visibly have:

- top highlight
- gradient body
- border
- hover state
- pressed state
- disabled state
- focus/default state

Primary/default action may use stronger Aqua blue.

Secondary buttons should use silver/gray Aqua appearance.


## 21. Menus and popovers

Menus should remain compact desktop menus.

Use:

- light background
- small type
- Aqua-blue selected item
- separators
- obvious disabled state
- restrained shadow

Avoid:

- floating mobile-style cards
- oversized rounded popovers
- transparent glass sheets


## 22. Settings / Preferences

Settings should take visual inspiration from Tiger-era System Preferences and Messenger Preferences.

Preferred patterns:

- compact form rows
- icon tabs or toolbar categories where appropriate
- native-looking checkboxes
- radio buttons
- popup/dropdown controls
- section separators
- compact labels

Do not turn settings into a modern mobile list with giant cells.


## 23. Motion

Animation should be short and functional.

Allowed:

- subtle hover transitions
- disclosure animation
- short panel appearance
- progress feedback

Avoid:

- springy mobile motion
- large-scale transforms
- bouncing cards
- continuous glass animation


## 24. Shadows

Shadows are restrained.

Internal control shadow should generally remain in the 1–2 px visual range.

No large diffuse card shadows.


## 25. Information density

AquaGram should be denser than current consumer mobile UI.

Think in terms of 1024×768 and 1280×800-era Mac desktop applications.

Do not waste large areas with whitespace solely for modern aesthetics.


## 26. Accessibility and platform correctness

Historical appearance must not reduce modern usability.

Keep:

- high-DPI correctness
- keyboard navigation
- visible focus
- screen-reader semantics
- sufficient contrast
- localization
- RTL compatibility where supported by existing architecture
- Telegram UI scaling

Aqua appearance is visual.

Accessibility regressions are not acceptable.


## 27. Upstream compatibility

Prefer presentation-layer changes.

Priority:

1. `.style`
2. palette
3. icons/assets
4. painting
5. layout
6. UI composition
7. presentation adapters

Avoid touching:

- MTProto
- networking
- authentication protocol
- local storage formats
- update logic
- calls backend
- media backend
- data semantics

AquaGram must remain realistically rebaseable on Telegram Desktop upstream.


## 28. Anti-goals

Reject a design if it can reasonably be described as:

- "Telegram but blue"
- "Telegram with gradients"
- "modern macOS with retro icons"
- "Windows Live Messenger skin"
- "glassmorphism"
- "Liquid Glass"
- "Y2K website"
- "Frutiger Aero wallpaper UI"

The correct reference is a native Mac OS X desktop application from approximately 2005.


## 29. Quality rule

When uncertain, compare the implementation against:

1. Microsoft Messenger for Mac
2. Apple HIG 2005
3. Panther/Tiger system applications
4. iChat AV

Do not invent modern visual conventions merely because they are easier to implement.
