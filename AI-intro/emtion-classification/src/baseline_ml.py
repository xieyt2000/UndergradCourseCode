"""
traditional machine learning method with sk-learn,
including naive bayes and SVM,
with bag of words.
Serve as baseline.
"""

import numpy as np
from scipy.stats import pearsonr
from sklearn.svm import LinearSVC
from sklearn.naive_bayes import MultinomialNB
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.metrics import classification_report
import function
from constants import *


def test(method, train_data, test_data):
    train_text, train_label, train_votes = function.data2vec(train_data)
    test_text, test_label, test_votes = function.data2vec(test_data)
    # train
    vec_model = CountVectorizer()
    train_text_vec = vec_model.fit_transform(train_text)
    if method == 'naive_bayes':
        cls = MultinomialNB()
    else:
        cls = LinearSVC()
    cls.fit(train_text_vec, train_label)
    # predict label
    test_text_vec = vec_model.transform(test_text)
    predicted_label = cls.predict(test_text_vec)
    print(classification_report(test_label, predicted_label, digits=4,
                                target_names=EMOTIONS_LIST, zero_division=0))
    # predict prob for coefficient
    if method == 'naive_bayes':
        predicted_votes = cls.predict_proba(test_text_vec)
    else:
        predicted_votes = cls.decision_function(test_text_vec)
    coefficient = 0
    for p_vote, t_vote in zip(predicted_votes, test_votes):
        coefficient += pearsonr(p_vote, t_vote)[0]
    coefficient /= len(predicted_votes)
    print(f"coefficient = {coefficient:.4f}")
