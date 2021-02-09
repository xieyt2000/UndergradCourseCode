import scrapy

count = 0


class TeamSpider(scrapy.Spider):
    name = 'team'

    start_urls = ['https://nba.hupu.com/']

    def parse(self, response):
        # follow links to team pages
        for team in response.css('.teamTeam'):
            href = team.attrib['href']
            yield response.follow(href, self.parse_team)

    def parse_team(self, response):
        global count
        count += 1
        name = response.css('.title-text::text').extract()[0].strip()
        print(name)
        nickname = response.xpath("//title/text()").extract()[0].strip().split("|")[0]
        print(nickname)
        time = response.xpath('//div[@class="font"]/p/text()')[0].extract().strip()[6:]
        if nickname=='篮网':
            print('debug')
        print(time)
        stadium_and_div = response.xpath('//div[@class="font"]/p/text()')[1].extract().strip()
        print(stadium_and_div)
        div_start = stadium_and_div.find("分区")
        stadium = stadium_and_div[3:div_start - 1]
        print(stadium)
        division = stadium_and_div[div_start + 3:]
        print(division)
        home_page_url = response.xpath("//a[contains(text(),'www.nba.com/')]").attrib['href']
        print(home_page_url)
        coach = response.xpath("//p[contains(text(),'主教练')]/text()").extract()[0].strip()[4:]
        print(coach)
        logo = response.xpath("//div[@class='img']//img").attrib['src']
        print(logo)
        intro = response.xpath("//div[@class='txt']/text()").extract()[0].strip()
        print(intro)
        rosters = {}
        no_number = -1
        for i in range(2, 30):
            row = response.xpath(f"//div[@class='a']//div[{i}]//span[1]")
            if len(row) < 1:
                break
            try:
                number = int(response.xpath(f"//div[@class='a']//div[{i}]//span[1]/text()").extract()[0].strip())
            except:
                number = no_number
                no_number -= 1
            if not number:
                number = no_number
                no_number -= 1
            player_name = response.xpath(f"//div[@class='a']//div[{i}]//span[2]//a[1]/text()").extract()[0].strip()
            rosters[number] = player_name
        print(rosters)
        print(count)
        yield {
            'fullname': name,
            'nickname': nickname,
            'enter_NBA_time': time,
            'stadium': stadium,
            'division': division,
            'home_page': home_page_url,
            'coach': coach,
            'logo_url': logo,
            'intro': intro,
            'rosters': rosters
        }
