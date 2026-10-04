# AquaGram Historical Reference Guide

This file defines the historical design sources that coding agents should consult before implementing AquaGram UI.

The sources are references only.

Do not directly copy copyrighted Apple or Microsoft artwork.

Create original AquaGram assets based on the visual language and behavior of the period.


## 1. Primary design target

### Microsoft Messenger for Mac 5.x

Use this to understand:

- messenger identity
- conversation layout
- Mac-specific Messenger chrome
- buddy/contact presentation
- conversation header structure
- early-2000s density
- brushed-metal integration

Historical release description:

https://www.mactech.com/2005/08/09/messenger-for-mac-5-0/

MacRumors historical Messenger 4 coverage/screenshots:

https://www.macrumors.com/2004/03/29/msn-messenger-4-0-images/


## 2. Apple Aqua Human Interface Guidelines

Recommended machine-readable historical archive:

https://github.com/johnzfitch/human-interface-markdown

For this project prioritize:

- 2005 Apple Human Interface Guidelines
- 2004 Apple Human Interface Guidelines
- 2002 Aqua Human Interface Guidelines

If the archive is available locally as a sibling checkout, inspect it before implementing custom controls.

Recommended local layout:

```text
TBuild/
├── tdesktop/
└── aqua-hig-reference/
```

Optional clone command outside the tdesktop repository:

```bash
cd ..
git clone --depth=1 \
  https://github.com/johnzfitch/human-interface-markdown.git \
  aqua-hig-reference
```

Useful searches:

```bash
rg -i "push button|default button|button" ../aqua-hig-reference
rg -i "search field|search" ../aqua-hig-reference
rg -i "toolbar|brushed metal" ../aqua-hig-reference
rg -i "scroll bar|scrollbar" ../aqua-hig-reference
rg -i "checkbox|radio button|pop-up" ../aqua-hig-reference
rg -i "split view|drawer|sheet" ../aqua-hig-reference
```

Before implementing a custom Aqua control, search the historical HIG for the corresponding control and inspect its examples/images where available.


## 3. Mac OS X 10.3 Panther

Use Panther references for:

- brushed metal
- Finder toolbar
- Finder sidebar
- search fields
- Aqua blue selection
- compact toolbars
- window chrome
- controls
- menu density

512 Pixels Aqua Screenshot Library:

https://512pixels.net/projects/aqua-screenshot-library/mac-os-x-10-3-panther/

GUIdebook Panther screenshots:

https://guidebookgallery.org/screenshots/macosx103/


## 4. Mac OS X 10.4 Tiger

Tiger is the primary operating-system-era reference because Microsoft Messenger for Mac 5.0 shipped in 2005.

Use Tiger references for:

- mature Aqua
- toolbar sizing
- application density
- System Preferences
- Safari
- Address Book
- Mail
- iChat AV
- search fields
- buttons
- menus
- inspector-like panels

512 Pixels Aqua Screenshot Library:

https://512pixels.net/projects/aqua-screenshot-library/mac-os-x-10-4-tiger/


## 5. iChat AV

Use iChat as a behavioral reference for a Mac-native instant messenger.

Use it for:

- buddy list hierarchy
- availability indicators
- buddy pictures
- status text
- compact messenger density
- groups
- Mac-native messaging conventions

Historical iChat Buddy List reference:

https://www.ralphjohns.co.uk/versions/ichat2/ichat2pics/slides/iChat2BuddyLIst.html


## 6. Reference precedence

When visual references conflict:

1. Microsoft Messenger for Mac 5.x
2. Apple HIG 2005
3. Mac OS X Tiger
4. Mac OS X Panther
5. iChat AV
6. current Telegram Desktop only for functionality

Do not use current macOS screenshots as visual references.


## 7. What NOT to use as primary reference

Do not use:

- macOS Big Sur or newer
- Liquid Glass
- iOS Messages
- Windows Live Messenger 2009/2011
- modern Electron apps
- modern Slack/Discord UI
- Material Design
- generic Y2K web design
- Frutiger Aero wallpapers
- modern glassmorphism

AquaGram is a native-looking 2005 Mac desktop messenger, not a nostalgia collage.
