# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://doc.scrapy.org/en/latest/topics/item-pipeline.html

import json


class HupunbaSpiderPipeline(object):
    def __init__(self):
        self.fp = open('teams.json', 'w', encoding='utf-8')

    def open_spider(self, spider):
        print("spider start")

    def process_item(self, item, spider):
        if(item['nickname']=='篮网'):
            print('debug')
        data = json.dumps(item)
        self.fp.write(data + '\n')

    def close_spider(self, spider):
        self.fp.close()
        print("spider end")
