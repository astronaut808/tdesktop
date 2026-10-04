# AquaGram

AquaGram is a visual fork of Telegram Desktop inspired by:

- Microsoft Messenger for Mac 5.x
- Mac OS X 10.3 Panther
- Mac OS X 10.4 Tiger
- iChat AV 2/3
- Apple Aqua Human Interface Guidelines from the 2003–2005 era

The goal is NOT to make "Telegram with a blue theme".

The goal is to make Telegram Desktop look and feel like a plausible native instant-messaging application that could have shipped on Mac OS X Tiger around 2005, while preserving Telegram functionality and keeping the fork reasonably rebaseable on upstream.

## Required reading for coding agents

Before implementing AquaGram UI work, read and follow:

1. `AGENTS.md`
2. `REVIEW.md`
3. `docs/aquagram/DESIGN.md`
4. `docs/aquagram/REFERENCES.md`
5. `docs/aquagram/COMPONENTS.md`
6. `docs/aquagram/ACCEPTANCE.md`
7. `docs/aquagram/MILESTONES.md`

Treat these files as the AquaGram product/design specification.

When historical appearance conflicts with usability, preserve Telegram functionality, accessibility, localization, scaling, and data correctness.

Prefer presentation-layer changes:

- `.style`
- palettes
- icons/assets
- painting
- layout
- UI composition
- presentation adapters

Avoid changes to:

- MTProto
- networking
- authentication protocol
- local storage formats
- Telegram data model unless strictly necessary
- update handling
- calls backend
- media backend

## Design identity

Reference priority:

1. Microsoft Messenger for Mac 5.x — messenger identity and conversation layout
2. Apple HIG 2005 — Aqua controls, interaction hierarchy, spacing philosophy
3. Mac OS X 10.3/10.4 — materials, chrome, density, window treatment
4. iChat AV 2/3 — buddy list and native Mac instant-messaging conventions
5. Telegram Desktop — functionality, not visual identity

Modern macOS visual conventions are NOT a design reference.

Explicit anti-goals:

- modern macOS
- Liquid Glass
- glassmorphism
- Material Design
- Windows Live Messenger for Windows
- Frutiger Aero wallpaper UI
- oversized rounded cards
- Telegram recolored blue
