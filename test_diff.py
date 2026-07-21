import sys
from unittest.mock import MagicMock

# Mock problematic dependencies before importing diff
sys.modules['ansiwrap'] = MagicMock()
sys.modules['watchdog'] = MagicMock()
sys.modules['colorama'] = MagicMock()
sys.modules['Levenshtein'] = MagicMock()
sys.modules['cxxfilt'] = MagicMock()

# Mock sys.argv to supply a dummy positional argument for diff.py's argument parser
sys.argv = ["diff.py", "dummy_start_symbol"]

from diff import pad_mnemonic


def test_pad_mnemonic_no_tab():
    assert pad_mnemonic("nop") == "nop"
    assert pad_mnemonic("") == ""
    assert pad_mnemonic("jr ra") == "jr ra"


def test_pad_mnemonic_single_tab_short():
    # 'add' has length 3. Format '<7s' will pad it with 4 spaces to 'add    '.
    # The formatted string is '{mn:<7s} {args}' which has an extra space.
    # Total spaces between 'add' and 'a' should be 4 (from padding) + 1 (separator) = 5 spaces.
    assert pad_mnemonic("add\ta, b, c") == "add     a, b, c"


def test_pad_mnemonic_single_tab_exact_width():
    # 'addiu32' has length 7. '<7s' will keep it as 'addiu32' (no padding).
    # Separator adds 1 space.
    assert pad_mnemonic("addiu32\ta, b") == "addiu32 a, b"


def test_pad_mnemonic_single_tab_long():
    # 'long_mnemonic' has length 13. '<7s' will keep it as 'long_mnemonic'.
    # Separator adds 1 space.
    assert pad_mnemonic("long_mnemonic\targ1") == "long_mnemonic arg1"


def test_pad_mnemonic_multiple_tabs():
    # 'add' has length 3, and args is 'foo\tbar' (since split occurs only on the first tab).
    # Expected output: 'add     foo\tbar'
    assert pad_mnemonic("add\tfoo\tbar") == "add     foo\tbar"
