"""Render every <module>/images/src/*.html fragment to <module>/images/<name>.png.

Usage: python3 tools/diagrams/render.py [module-folder ...]
Needs `pip install playwright` and either a Chrome with CDP on :29229 or `playwright install chromium`.
"""
import pathlib
import sys

from playwright.sync_api import sync_playwright

ROOT = pathlib.Path(__file__).resolve().parents[2]
CSS = (pathlib.Path(__file__).parent / "style.css").read_text()


def sources(args):
    dirs = [ROOT / a for a in args] if args else sorted(p for p in ROOT.iterdir() if p.is_dir())
    for d in dirs:
        yield from sorted((d / "images" / "src").glob("*.html"))


def main():
    with sync_playwright() as p:
        try:
            browser = p.chromium.connect_over_cdp("http://localhost:29229")
        except Exception:
            browser = p.chromium.launch()
        page = browser.new_context(device_scale_factor=2).new_page()
        for src in sources(sys.argv[1:]):
            page.set_content(f"<html><head><meta charset='utf-8'><style>{CSS}</style></head><body>{src.read_text()}</body></html>")
            out = src.parent.parent / f"{src.stem}.png"
            page.locator(".card").first.screenshot(path=str(out))
            print(out.relative_to(ROOT))
        page.close()


if __name__ == "__main__":
    main()
