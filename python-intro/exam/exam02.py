from html.parser import HTMLParser
from html.parser import HTMLParser
from html.entities import name2codepoint

attrib_counter = 0
tables=[]
countries = []
country = []
in_th = False
first_table=True

class MyHTMLParser(HTMLParser):
    def handle_starttag(self, tag, attrs):
        global attrib_counter
        global countries
        global country
        global in_th
        global first_table
        print("Start tag:", tag)
        if tag != 'th':
            return
        if len(attrs) > 0:
            if first_table:
                first_table=False
            countries.apeend(country)
            country=[]
            tables.append(countries)
            countries=[]
            return
        if attrib_counter == 4:
            attrib_counter = 0
            countries.apeend(country)
            country = []
        attrib_counter += 1
        in_th = True

    def handle_endtag(self, tag):
        global in_th
        print("End tag  :", tag)
        if tag != 'th':
            return
        in_th = False

    def handle_data(self, data):
        print("Data     :", data)
        if in_th: country.append(data.strip)

    def handle_comment(self, data):
        print("Comment  :", data)

    def handle_entityref(self, name):
        c = chr(name2codepoint[name])
        print("Named ent:", c)

    def handle_charref(self, name):
        if name.startswith('x'):
            c = chr(int(name[1:], 16))
        else:
            c = chr(int(name))
        print("Num ent  :", c)

    def handle_decl(self, data):
        print("Decl     :", data)


parser = MyHTMLParser()
with open('origin.html', 'r') as f:
    parser.feed(f.read())
tables.append(countries)
for i in range(25):
    file_name='A'+i
    with open(f'{file_name}.csv', 'w') as f:
        f.write('国家或地区,中文全称,英文简称,ISO 代码\n')
        for j in tables[i]:
            for k in j:
                for q in range(4):
                    f.write(k[q])
                    if(q==4):
                        f.write('\n')
                    else:
                        f.write(',')