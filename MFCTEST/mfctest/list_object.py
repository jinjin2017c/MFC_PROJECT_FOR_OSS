import oss2
from itertools import islice
auth = oss2.Auth('LTAIomCMBttjFRJj', 'mrlRsN52kfdoqPJYCZxyaNzn1EsniF')
bucket = oss2.Bucket(auth, 'oss-cn-beijing.aliyuncs.com','jinjinfortest')
for obj in oss2.ObjectIterator(bucket, delimiter='/'):
    if obj.is_prefix():  
        print('directory: ' + obj.key)
    else:                
        print('file: ' + obj.key)