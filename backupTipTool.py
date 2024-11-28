from argparse import *
from ctypes import *
from json import *

class CDataJSONEncoder(JSONEncoder):
    def default(self, obj):
        if isinstance(obj, (bool, int, float, str)):
            return obj
        if isinstance(obj, bytes):
            return obj.decode("utf-8")
        if isinstance(obj, (Structure, Union)):
            result = {}
            for key, *_ in getattr(obj, '_fields_', []):
                value = getattr(obj, key)
                if key.startswith('_'):
                    continue
                result[key] = self.default(value)
            return result
        if isinstance(obj, Array):
            result = []
            for i in obj:
                value = self.default(i)
                if value["tipname"] == "":
                    continue
                result.append(value)
            return result
        return JSONEncoder.default(self, obj)

class backup_data_t(Structure):
    _fields_ = [('profile', c_uint8),
                ('tipname', c_char * 9),
                ('cal_250', c_uint16),
                ('cal_400', c_uint16),
                ('_padding', c_uint16)]

class backup_tips_t(Structure):
    _fields_ = [('_tipSig', c_char * 12),
                ('tipNums', c_uint32),
                ('tipData', backup_data_t * 63)]

def listTips(data: bytes):
    tips = backup_tips_t.from_buffer_copy(data)
    conf = dumps(tips, cls=CDataJSONEncoder, indent=2)
    print(conf)

def dumpTips(data: bytes, json: str):
    tips = backup_tips_t.from_buffer_copy(data)
    conf = dumps(tips.tipData[0 : tips.tipNums], cls=CDataJSONEncoder, indent=2)
    open(json, "w").write(conf)

def saveTips(json: str, file: str, offs: int):
    conf = loads(open(json, "r").read())
    tips = backup_tips_t()
    tips._tipSig = "#BACKUPTIPS#".encode("utf-8")
    tips.tipNums = len(conf)
    for i in range(tips.tipNums):
        tips.tipData[i].profile = conf[i]["profile"]
        tips.tipData[i].tipname = conf[i]["tipname"].encode("utf-8")
        tips.tipData[i].cal_250 = conf[i]["cal_250"]
        tips.tipData[i].cal_400 = conf[i]["cal_400"]
    fd = open(file, "r+b")
    fd.seek(offs)
    fd.write(bytes(tips))
    fd.close()

if __name__ == "__main__":
    parser = ArgumentParser()
    subparsers = parser.add_subparsers(dest="mode")

    list_parser = subparsers.add_parser("list", help="List backup tips in binary file")

    dump_parser = subparsers.add_parser("dump", help="Dump backup tips to binary file")
    dump_parser.add_argument("-c", "--conf", help="JSON config file for binary", required=True)

    save_parser = subparsers.add_parser("save", help="Save backup tips to binary file")
    save_parser.add_argument("-c", "--conf", help="JSON config file for binary", required=True)

    parser.add_argument("binary", help="Binary file")

    try:
        args = parser.parse_args()
        # args = parser.parse_args(["save", "-c", "123.json", "KSGER_GX_V2.1S_a0d8490f.bin"])
    except:
        exit(-1)

    data = open(args.binary, "rb").read()
    offs = data.rfind(b"#BACKUPTIPS#")

    if args.mode == "list":
        listTips(data[offs:])
    elif args.mode == "dump":
        dumpTips(data[offs:], args.conf)
    elif args.mode == "save":
        saveTips(args.conf, args.binary, offs)