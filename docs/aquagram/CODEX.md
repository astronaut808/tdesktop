# Codex Instructions for AquaGram UI Work

Use this file when beginning AquaGram implementation work after the baseline Debug build is proven.

Before making UI changes:

1. Read repository `AGENTS.md`.
2. Read repository `REVIEW.md`.
3. Read:
   - `AQUAGRAM.md`
   - `docs/aquagram/DESIGN.md`
   - `docs/aquagram/REFERENCES.md`
   - `docs/aquagram/COMPONENTS.md`
   - `docs/aquagram/ACCEPTANCE.md`
   - `docs/aquagram/MILESTONES.md`
4. Inspect the current Telegram Desktop UI/style architecture.
5. If available, inspect a sibling checkout of:
   `johnzfitch/human-interface-markdown`
6. Use historical HIG/reference material before inventing a custom control.

## Work rules

- Implement one milestone at a time.
- Do not attempt the whole redesign in one patch.
- Prefer `.style`, palette, assets, painting and presentation-layer changes.
- Keep all scalable dimensions in `.style` where appropriate.
- Do not hardcode API credentials.
- Do not build Release for routine UI work.
- Do not change MTProto/networking/storage/auth/update/media/calls backend for styling.
- Preserve Telegram functionality.
- Keep the fork realistically rebaseable on upstream.
- Validate visual milestones with screenshots.
- Compilation alone is not visual acceptance.

## Design rule

If a result looks like "Telegram but blue", the implementation is wrong.

The target is:

**Microsoft Messenger for Mac 5.x + Mac OS X Tiger/Panther Aqua + iChat conventions, applied to Telegram Desktop functionality.**

## Reference order

1. Microsoft Messenger for Mac 5.x
2. Apple HIG 2005
3. Mac OS X Tiger
4. Mac OS X Panther
5. iChat AV
6. Telegram Desktop functionality

Do not use current macOS UI as a visual source.

## First implementation milestone

After M0 baseline, begin with:

**M1 — Aqua Foundation**

Do not jump directly to message-layout rewrites.

At the end of each milestone report:

- files changed
- architecture used
- screenshots
- visual comparison against the spec
- functional regressions
- known deviations
- Debug build result
- git status
