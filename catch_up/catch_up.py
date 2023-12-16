#!/usr/bin/env python3

import mechanicalsoup

def fill_and_submit_form(user_input):
    url = "https://example.com"  # Replace with your actual URL
    field_identifier = "input#ffsearchname"  # Corrected field identifier
    search_button_selector = "input.ffsearchbutton"  # Selector for the search button
    add_all_button_selector = "a.shadedoutline.addallbutton"  # Selector for the "Lägg till alla" button
    third_button_selector = "input#objectbasketgo"  # Selector for the third button

    # Create a browser object
    browser = mechanicalsoup.Browser()

    # Open the URL
    page = browser.get(url)

    # Fill the form
    form = page.soup.select("form")
    form.select(field_identifier)[0]["value"] = user_input

    # Submit the form
    page_after_submit = browser.submit(form, page.url)

    # Click the search button
    search_button = page_after_submit.soup.select(search_button_selector)
    if search_button:
        browser.follow_link(search_button[0])

    # Click the "Lägg till alla" button
    add_all_button = page_after_submit.soup.select(add_all_button_selector)
    if add_all_button:
        browser.follow_link(add_all_button[0])

    # Click the third button
    third_button = page_after_submit.soup.select(third_button_selector)
    if third_button:
        browser.follow_link(third_button[0])

    # Print the resulting URL
    print("Resulting URL:", browser.get_current_page().url)

def main():
    # Get user input
    user_input = input("Enter the value for the form field: ")

    # Fill and submit the form
    fill_and_submit_form(user_input)

if __name__ == "__main__":
    main()
