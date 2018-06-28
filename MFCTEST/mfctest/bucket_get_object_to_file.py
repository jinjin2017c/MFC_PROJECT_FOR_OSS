from __future__ import print_function
import os,sys
import oss2
from time import time
auth = oss2.Auth('LTAIomCMBttjFRJj', 'mrlRsN52kfdoqPJYCZxyaNzn1EsniF')
bucket = oss2.Bucket(auth, 'oss-cn-beijing.aliyuncs.com','jinjinfortest')
start_time = time()
def percentage(consumed_bytes,total_bytes):
    if total_bytes:
        rate = int(100*(float(consumed_bytes)/float(total_bytes)))
        dur_time = float(time())-float(start_time)
        speed = (float(consumed_bytes)/float(dur_time))/(1000)
        print('\r{0}% {1} KB/s  '.format(rate,speed), end='')
        sys.stdout.flush()
bucket.get_object_to_file('story.txt','downloadfile.txt',progress_callback = percentage)