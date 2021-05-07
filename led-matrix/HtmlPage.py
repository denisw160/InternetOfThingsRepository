# This a simple Python script for transform the HtmlPage.html to HtmlPage.h
import re


def transform():
    html = open('HtmlPage.html', 'r').read()
    print_output("Input", html)

    escaped = html
    escaped = escaped.replace("\n", " ")  # Remove new lines
    escaped = re.sub(r"<!--.+?-->", "", escaped)  # Remove comments
    escaped = re.sub(r"\s\s+", " ", escaped)  # Remove multiple spaces
    escaped = escaped.replace("\"", "\\\"")  # Escape quotation marks
    print_output("Escaped", escaped)

    template = open('HtmlPage.h-template', 'r').read()
    template = template.replace("@@html@@", escaped)
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
    transform()
