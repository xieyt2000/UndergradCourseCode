import scrapy


class NewsSpider(scrapy.Spider):
    name = 'news'

    start_urls = ['https://voice.hupu.com/nba']

    def parse(self, response):
        # follow links to team pages
        for news_piece in response.xpath('//h4/a'):
            news_piece_href = news_piece.attrib['href']
            yield response.follow(news_piece_href, self.parse_news)
        next_page_href = response.xpath('//a[contains(text(),"下一页")]').attrib['href']
        yield response.follow(next_page_href, self.parse)

    def parse_news(self, response):
        item = {}
        title = response.xpath("//h1[@class='headline']/text()").extract()[0].strip()
        # print(title)
        item['title'] = title
        content_div = response.xpath("//div[@class='artical-main-content']//text()").extract()
        body_text = ""
        for p in content_div:
            body_text = body_text + p.strip() + '\n'
        # print(body_text)
        item['content'] = body_text
        id = response.request.url.split('/')[-1].split('.')[0]
        # print(id)
        item['id'] = id
        source = response.xpath("//span[@class='comeFrom']//a/text()").extract()[0].strip()
        item['source'] = source
        # print(source)
        time = response.xpath("//span[@id='pubtime_baidu']/text()").extract()[0].strip()
        item['time'] = time
        # print(time)
        yield item
