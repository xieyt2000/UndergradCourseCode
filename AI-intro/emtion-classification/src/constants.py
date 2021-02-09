# sina data path
SINA_FOLDER = "../data/sina"
TRAIN_PATH = SINA_FOLDER + "/train.json"
TEST_PATH = SINA_FOLDER + "/test.json"
WORD2ID_PATH = "../data/word2id.json"
WORD_COUNT_PATH = "../data/word_count.json"
# embedding path
EMBEDDING_FOLDER = "../data/embedding"
ORI_EMB_PATH = EMBEDDING_FOLDER + "/sgns.sogounews.bigram-char"
EMBEDDING_PATH = EMBEDDING_FOLDER + '/embedding.json'
# net path
NET_CONFIG_FOLDER = "../data/net_config"
NET_FOLDER = "../data/net"
# output path
RES_PATH = "../data/result.txt"

# parameter
EMBEDDING_DIM = 300

# data
EMOTIONS_DICT = {'感动': 0, '同情': 1, '无聊': 2, '愤怒': 3, '搞笑': 4,
                 '难过': 5, '新奇': 6, '温馨': 7}
EMOTIONS_LIST = ['感动', '同情', '无聊', '愤怒', '搞笑', '难过', '新奇', '温馨']
EMOTIONS_NUM = len(EMOTIONS_LIST)

# token
UNKNOWN = 'U'  # unknown token deal with out of vocabulary words
PADDING = 'P'
