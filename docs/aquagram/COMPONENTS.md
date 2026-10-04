# AquaGram Component Mapping

This file maps Telegram Desktop concepts to AquaGram presentation.

The rule is:

**Preserve Telegram semantics. Change presentation.**

Do not redesign Telegram's data model merely to imitate MSN.


| Telegram Desktop | AquaGram representation | Primary reference |
|---|---|---|
| Dialog list | Buddy List | Messenger / iChat |
| Folder header | Buddy group header | iChat / MSN |
| Current user/profile block | My Status block | MSN |
| Search | Aqua search field | Finder / Safari |
| Selected dialog | Aqua blue selection | Finder sidebar |
| Unread dialog | Compact bold/unread treatment | Messenger / Mail |
| Chat top bar | Messenger conversation toolbar | Messenger 5 |
| Call/video | Pictorial toolbar actions | Messenger / iChat |
| Ordinary text message | `Name says: (time)` conversation log | MSN |
| Reply | Inset quote | Aqua content panel |
| Forward | Compact metadata block | Hybrid |
| Photo/video | Bordered media object | Hybrid |
| File | Aqua attachment object | Messenger + Telegram |
| Voice | Compact Aqua media control | Hybrid |
| Reaction | Mini Aqua control | Hybrid |
| Poll | Framed content panel | Hybrid |
| Service message | Centered/small system line | Messenger / iChat |
| Composer actions | Toolbar | MSN |
| Composer field | Aqua text area | Apple HIG |
| Send action | Default Aqua push button | Apple HIG |
| Right info sidebar | Contact inspector | Address Book |
| Settings | Preferences window | Tiger applications |
| Checkbox/radio | Classic Aqua controls | Apple HIG |
| Menus | Aqua menu | Apple HIG |
| Progress | Aqua progress control | Apple HIG |


## 1. Sidebar

### 1.1 Identity block

Display:

- avatar
- current display name
- Telegram-derived status/presence
- optional short status text

Presentation should resemble an MSN/iChat self-status area.

Do not invent presence information.


### 1.2 Search

Use classic Aqua search-field presentation.

Keep existing Telegram search semantics.


### 1.3 Dialog rows

Visual content:

- presence indicator where meaningful
- avatar
- display name
- message preview/status
- time if needed
- unread indicator
- mute state

Selection should use a classic Aqua blue gradient.

Do not make each dialog a floating rounded card.


### 1.4 Folder/group headers

Use compact disclosure-style headers.

Telegram folders remain Telegram folders.

Do not introduce fake Friends/Offline groups unless backed by real existing grouping semantics.


## 2. Conversation header

Map existing Telegram header functionality to a Messenger-like toolbar.

Left:

- avatar
- conversation name
- status / last seen

Right:

- Call
- Video
- Search
- Info
- other required Telegram actions

Do not remove existing actions solely for historical fidelity.


## 3. Ordinary messages

Preferred 1:1 text presentation:

```text
Chris says: (20:42)

Привет.
Как дела?
```

No standard Telegram bubble around ordinary text.

Outgoing/incoming identity should be communicated by sender heading and subtle color differences rather than left/right mobile bubbles.


## 4. Group messages

Group messages must clearly identify sender.

Possible presentation:

```text
Alice says: (20:40)
...

Chris says: (20:41)
...
```

Use stable per-sender visual distinction where existing Telegram logic already provides identity colors.

Do not sacrifice readability for historical mimicry.


## 5. Consecutive messages

Avoid repeating the full sender heading for every tiny consecutive message where it creates visual noise.

Possible rule:

- show sender heading at the start of a new speaker turn
- continue body text below
- show compact time metadata where necessary
- restart heading after meaningful temporal separation, reply context change, or speaker change

Exact grouping logic should reuse existing Telegram message-grouping semantics where possible.


## 6. Replies

Render as:

- thin Aqua blue vertical rule
- sender name
- one/two lines preview
- optional pale blue inset panel

No nested modern bubbles.


## 7. Media

Media retains Telegram functionality.

Use framed content objects:

- low radius
- 1 px border
- subtle Aqua background
- compact metadata

Media itself should remain visually dominant.


## 8. Reactions

Render existing Telegram reactions as compact Aqua mini-controls.

Do not remove reaction functionality.


## 9. Composer

Structure:

```text
[ Formatting ] [ Emoticons ] [ Attach / Send File ] ...

+------------------------------------------------------+
| Message text area                                    |
|                                                      |
+------------------------------------------------------+

                                             [ Send ]
```

This is a visual model, not a strict requirement to rearrange every existing Telegram action immediately.

Implement in incremental milestones.


## 10. Info/profile panel

Use an Address Book / inspector-inspired presentation.

Possible hierarchy:

- avatar
- name
- presence/status
- username
- notification setting
- shared media
- files
- links
- groups/common context

Preserve Telegram data and actions.


## 11. Settings

Presentation target:

- Tiger-era preferences
- compact forms
- section headers
- icon tabs where practical
- Aqua checkbox/radio/dropdown/button treatment

Do not convert settings into oversized mobile cards.


## 12. System/service messages

Use compact centered or lightly framed system text.

Examples:

- joined group
- pinned message
- call event
- topic created

Keep them readable but visually secondary.


## 13. Unread state

Unread must remain obvious.

Recommended combination:

- semibold/bold name
- compact count badge
- subtle background emphasis

Selected and unread states must not be confused.


## 14. Error/warning states

Do not make all errors blue.

Preserve semantic warning/error color distinction.

Aqua styling applies to shape/material, not to erasing information hierarchy.


## 15. Context menus

Keep existing command set.

Restyle presentation only where feasible:

- compact
- light background
- blue selected item
- separators
- proper disabled state


## 16. Functional invariants

AquaGram presentation must preserve:

- sending
- editing
- deleting
- forwarding
- replying
- reactions
- media playback
- downloads
- voice messages
- calls
- search
- navigation
- topics
- bots
- polls
- keyboard shortcuts
- accessibility semantics
- localization
- scaling
