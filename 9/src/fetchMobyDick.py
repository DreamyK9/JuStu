import argparse, math
from webdriver_manager.firefox import GeckoDriverManager
from selenium import webdriver
from selenium.webdriver.firefox.service import Service
from selenium.webdriver.common.by import By
# Waiting
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

def main():
    parser = argparse.ArgumentParser(description="Download the whole text of Moby Dick and output it to a file.")
    # Optional arguments
    parser.add_argument('-o', "--output", help="output file", default="MobyDick", dest="output")
    parser.add_argument('-g', "--gui", action="store_true", help="show browser gui (don't start headless)", dest="gui")
    parser.add_argument('-s', "--silent", action="store_true", help="silent mode: no status messages", dest="silent")
    parser.add_argument('-b', "--beginning", type=int, default=0, help="first page to download", dest="begin")
    parser.add_argument('-e', "--end", type=int, default=math.inf, help="last page to download", dest="end")
    #########
    args = parser.parse_args()

    if not args.silent:
        print("Starting WebDriver...")
    # Setup WebDriver
    options = webdriver.FirefoxOptions()
    if not args.gui:
        options.headless = True
    driver = webdriver.Firefox(service=Service(GeckoDriverManager().install()), options=options)

    if not args.silent:
        print("Fetching Page Links...")
    # Fetch Page Links
    driver.get("https://www.sparknotes.com/lit/mobydick/full-text/")
    link_elements = driver.find_elements(By.XPATH, "/html/body/div[8]/div[1]/div/ul/li/a")
    
    links = []
    for element in link_elements:
        links.append(element.get_property('href'))
    
    if not args.silent:
        print("Downloading Text...")
    # Download Text
    upper_cap = args.end if args.end != math.inf else len(links)
    total_text = ""
    for c, l in enumerate(links, 1):
        site_status = f"{c:03d} of {upper_cap:03d}" 
        
        if c < args.begin:
            continue

        if c > args.end:
            break

        driver.get(l)
        text_elements = WebDriverWait(driver, 20).until(
            EC.presence_of_all_elements_located((By.TAG_NAME, "p"))
        )

        current_text = ""
        for c2, element in enumerate(text_elements, 1):
            print(f"Downloaded Paragraph {c2:03d} of {len(text_elements):03d} on page {site_status:s}", end='\r')
            current_text += element.text + " "
        total_text += current_text.strip() + '\n'

    driver.quit()

    if not args.silent:
        print(f"\nFinished downloading {upper_cap - args.begin} pages of Moby Dick")
    # Output Text
    with open(args.output + ".txt", 'w', encoding='utf-8') as f:
        f.write(total_text)
    
    if not args.silent:
        print(f"Successfully saved to {args.output}.txt")
        print("Exiting...")

if __name__ == '__main__':
    main()
