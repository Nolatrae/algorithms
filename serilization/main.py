import struct
from enum import Enum

class Alignment(Enum):
    HORIZONTAL = 1
    VERTICAL = 2

class Widget():

    def __init__(self, parent):
        self.parent = parent
        self.childrens = []

        if self.parent is not None:
            self.parent.add_children(self)

    def add_children(self, children: "Widget"):
        self.childrens.append(children)

    def to_binary(self):
        class_name = self.__class__.__name__.encode()
        res = struct.pack("i", len(class_name)) + class_name

        if isinstance(self, Layout):
            alignment_value = self.alignment.value
            res += struct.pack("i", alignment_value)
        elif isinstance(self, LineEdit):
            max_length = self.max_length
            res += struct.pack("i", max_length)
        elif isinstance(self, ComboBox):
            items = [str(item) for item in self.items]
            items_str = ";".join(items).encode()
            res += struct.pack("i", len(items_str)) + items_str
        elif isinstance(self, MainWindow):
            title_str = self.title.encode()
            res += struct.pack("i", len(title_str)) + title_str

        children_data = b"".join([child.to_binary() for child in self.childrens])
        res += struct.pack("i", len(children_data)) + children_data

        return res

    @classmethod
    def from_binary(cls, binary_data, parent=None):
        class_name_length = struct.unpack("i", binary_data[:4])[0]
        temp_cursor = 4
        class_name = binary_data[temp_cursor:temp_cursor + class_name_length].decode()
        temp_cursor += class_name_length

        length_data = struct.unpack("i", binary_data[temp_cursor:temp_cursor + 4])[0]
        temp_cursor += 4
        property_value = binary_data[temp_cursor:temp_cursor + length_data].decode()
        temp_cursor += length_data

        root_element = None
        if class_name == "MainWindow":
            root_element = cls(property_value)
        elif class_name == "Layout":
            temp_cursor -= length_data
            root_element = Layout(parent, length_data)
        elif class_name == "LineEdit":
            temp_cursor -= length_data
            root_element = LineEdit(parent, length_data)
        elif class_name == "ComboBox":
            root_element = ComboBox(parent, property_value)

        children_length = struct.unpack("i", binary_data[temp_cursor:temp_cursor + 4])[0]
        temp_cursor += 4
        children_data = binary_data[temp_cursor:]

        cursor = 0
        while cursor < children_length:
            child_node, child_cursor = root_element.from_binary(children_data[cursor:], parent=root_element)
            cursor += child_cursor

        return root_element, temp_cursor + cursor

    def __str__(self):
        return f"{self.__class__.__name__}{self.childrens}"

    def __repr__(self):
        return str(self)

class MainWindow(Widget):

    def __init__(self, title: str):
        super().__init__(None)
        self.title = title

class Layout(Widget):

    def __init__(self, parent, alignment: Alignment):
        super().__init__(parent)
        self.alignment = alignment

class LineEdit(Widget):

    def __init__(self, parent, max_length: int = 10):
        super().__init__(parent)
        self.max_length = max_length

class ComboBox(Widget):

    def __init__(self, parent, items):
        super().__init__(parent)
        self.items = items


app = MainWindow("Application")
layout1 = Layout(app, Alignment.HORIZONTAL)
layout2 = Layout(app, Alignment.VERTICAL)

edit1 = LineEdit(layout1, 20)
edit2 = LineEdit(layout1, 30)

box1 = ComboBox(layout2, [1, 2, 3, 4])
box2 = ComboBox(layout2, ["a", "b", "c"])

print(app, end='\n\n')

bts = app.to_binary()
print(f"Binary data length {len(bts)}", end='\n\n')
print(f"Binary data {bts}", end='\n\n')

new_app = MainWindow.from_binary(bts)
print(new_app[0])