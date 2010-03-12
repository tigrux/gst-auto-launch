#!/usr/bin/env/python

import sys

def convert_from_py_to_xml(orig_py_file):
    if not orig_py_file.endswith(".py"):
        print "File %s does not end in .py" % orig_py_file
        return
    new_xml_file = orig_py_file.replace(".py", ".xml")
    pipelines_py = eval(open(orig_py_file).read())
    output = open(new_xml_file, "w")
    for pipeline in pipelines_py:
        output.write('<pipeline id="%s">' % pipeline)
        output.write('%s' % pipelines_py[pipeline])
        output.write('</pipeline>\n\n')
    output.close()
    print "Written file %s" % new_xml_file


def main(argv):
    for arg in argv:
        convert_from_py_to_xml(arg)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print "Converts from pipelines.py to pipelines.xml"
        print "Usage: %s <pipelines.py>" % sys.argv[0]
    else:
        main(sys.argv[1:])

