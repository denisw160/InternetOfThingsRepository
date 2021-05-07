# This a simple Python script for transform the HtmlPage.html to HtmlPage.h
import re
import os.path


def transform(file, tag):
    html = open(file, "r").read()
    print_output("Input", html)

    escaped = html
    escaped = escaped.replace("\n", " ")  # Remove new lines
    escaped = re.sub(r"<!--.+?-->", "", escaped)  # Remove comments
    escaped = re.sub(r"\s\s+", " ", escaped)  # Remove multiple spaces
    escaped = escaped.replace("\"", "\\\"")  # Escape quotation marks
    print_output("Escaped", escaped)

    template_file = "HtmlPage.h-template"
    if os.path.isfile("HtmlPage.h"):
        template_file = "HtmlPage.h"

    template = open(template_file, "r").read()
    template = template.replace(tag, escaped)
    print_output("Output", template)

    f = open("HtmlPage.h", "w")
    f.write(template)
    f.close()


def print_output(title, output):
    print("")
    print("*** " + title + " ***")
    print(output)
    print("Length: " + str(len(output)))


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    os.remove("HtmlPage.h")
    transform("HtmlPage_Root.html", "@@rootPage@@")
    transform("HtmlPage_Success.html", "@@successPage@@")
    transform("HtmlPage_Failed.html", "@@failedPage@@")
    transform("HtmlPage_NotFound.html", "@@notFoundPage@@")
