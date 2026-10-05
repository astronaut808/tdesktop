import importlib.util
from pathlib import Path
import tempfile
import unittest

MODULE_PATH = Path(__file__).resolve().parents[1] / 'aquagram_overlay.py'
spec = importlib.util.spec_from_file_location('aquagram_overlay', MODULE_PATH)
overlay = importlib.util.module_from_spec(spec)
spec.loader.exec_module(overlay)
TOOLKIT = MODULE_PATH.parents[1] / 'lib_ui'


class OverlayTests(unittest.TestCase):
    def test_current_pinned_sources_transform(self):
        import hashlib
        for name, expected in overlay.PINS.items():
            original = (TOOLKIT / name).read_bytes()
            self.assertEqual(hashlib.sha256(original.replace(b"\r\n", b"\n")).hexdigest(), expected)
            transformed = overlay.transform(name, original.decode())
            self.assertIn('ui/aquagram/aquagram.h', transformed)
            self.assertEqual((TOOLKIT / name).read_bytes(), original)

    def test_crlf_checkout_is_equivalent_and_unchanged(self):
        import sys
        from unittest.mock import patch
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            source, output = root / 'source', root / 'output'
            for name in overlay.PINS:
                path = source / name
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_bytes((TOOLKIT / name).read_bytes().replace(b'\r\n', b'\n').replace(b'\n', b'\r\n'))
            originals = {name: (source / name).read_bytes() for name in overlay.PINS}
            with patch.object(sys, 'argv', ['overlay', str(source), str(output)]):
                overlay.main()
            for name in overlay.PINS:
                self.assertTrue((output / name).is_file())
                self.assertEqual((source / name).read_bytes(), originals[name])
                self.assertNotIn(b'\r\n', (output / name).read_bytes())

    def test_missing_or_duplicate_anchor_is_rejected(self):
        for text in ('missing', 'anchor anchor'):
            with self.assertRaisesRegex(RuntimeError, 'hook drift'):
                overlay.replace_once(text, 'anchor', 'changed', 'fixture')

    def test_changed_toolkit_is_rejected_before_output(self):
        import sys
        from unittest.mock import patch
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            source, output = root / 'source', root / 'output'
            source.mkdir()
            first = next(iter(overlay.PINS))
            path = source / first
            path.parent.mkdir(parents=True)
            path.write_text('changed upstream input')
            with patch.object(sys, 'argv', ['overlay', str(source), str(output)]):
                with self.assertRaisesRegex(RuntimeError, 'input changed'):
                    overlay.main()
            self.assertFalse(output.exists())


if __name__ == '__main__':
    unittest.main()
