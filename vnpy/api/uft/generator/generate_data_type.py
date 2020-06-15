""""""
from typing import Dict

TYPE_CPP2PY: Dict[str, str] = {
    "int": "int",
    "char": "char",
    "double": "double",
    "short": "int",
}


class DataTypeGenerator:
    """DataType生成器"""

    def __init__(self, filename: str, prefix: str):
        """Constructor"""
        self.filename: str = filename
        self.prefix: str = prefix

    def run(self) -> None:
        """主函式"""
        self.f_cpp = open(self.filename, "r")
        self.f_define = open(f"{self.prefix}_constant.py", "w")
        self.f_typedef = open(f"{self.prefix}_typedef.py", "w")

        for line in self.f_cpp:
            self.process_line(line)

        self.f_cpp.close()
        self.f_define.close()
        self.f_typedef.close()

        print("DataType生成完畢")

    def process_line(self, line: str) -> None:
        """處理每行"""
        line = line.replace("\n", "")
        line = line.replace(";", "")

        if line.startswith("#define"):
            self.process_define(line)
        elif line.startswith("typedef"):
            self.process_typedef(line)

    def process_define(self, line: str) -> None:
        """處理常量定義"""
        words = line.split(" ")
        words = [word for word in words if word]
        if len(words) < 3:
            return

        name = words[1]
        value = words[2]

        new_line = f"{name} = {value}\n"
        self.f_define.write(new_line)

    def process_typedef(self, line: str) -> None:
        """處理型別定義"""
        words = line.split(" ")
        words = [word for word in words if word != " "]

        name = words[2]
        typedef = TYPE_CPP2PY[words[1]]

        if typedef == "char":
            if "[" in name:
                typedef = "string"
                name = name[:name.index("[")]

        new_line = f"{name} = \"{typedef}\"\n"
        self.f_typedef.write(new_line)


if __name__ == "__main__":
    generator = DataTypeGenerator("../include/uft/HSDataType.h", "uft")
    generator.run()
