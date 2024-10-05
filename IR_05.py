import requests
from bs4 import BeautifulSoup
from urllib.parse import urljoin, urlparse


def fetch_page(url):
    try:
        response = requests.get(url)
        response.raise_for_status()
        return BeautifulSoup(response.text, "html.parser")
    except requests.exceptions.RequestException as e:
        print(f"Failed to fetch {url}: {e}")
        return None


def extract_links(soup, base_url):
    links = set()
    for anchor in soup.find_all("a", href=True):
        href = anchor["href"]
        full_url = urljoin(base_url, href)
        if urlparse(full_url).scheme in ["http", "https"]:
            links.add(full_url)
    return links


def crawl(start_url, depth=2):
    visited = set()
    to_visit = [(start_url, 0)]

    while to_visit:
        current_url, current_depth = to_visit.pop(0)
        if current_url in visited or current_depth > depth:
            continue
        print(f"Crawling: {current_url} (Depth: {current_depth})")
        visited.add(current_url)
        soup = fetch_page(current_url)
        if soup is None:
            continue
        links = extract_links(soup, current_url)
        for link in links:
            if link not in visited:
                to_visit.append((link, current_depth + 1))


start_url = "https://en.wikipedia.org/wiki/C_(programming_language)"
crawl(start_url, depth=2)
