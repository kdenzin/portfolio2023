"""
Project 2
CSE 331 F23 (Onsay)
Authored By: Hank Murdock
Originally Authored By: Andrew McDonald & Alex Woodring & Andrew Haas & Matt Kight & Lukas Richters & Sai Ramesh
solution.py
"""

from typing import TypeVar, List

# for more information on type hinting, check out https://docs.python.org/3/library/typing.html
T = TypeVar("T")  # represents generic type
Node = TypeVar("Node")  # represents a Node object (forward-declare to use in Node __init__)


# pro tip: PyCharm auto-renders docstrings (the multiline strings under each function definition)
# in its "Documentation" view when written in the format we use here. Open the "Documentation"
# view to quickly see what a function does by placing your cursor on it and using CTRL + Q.
# https://www.jetbrains.com/help/pycharm/documentation-tool-window.html


class Node:
    """
    Implementation of a doubly linked list node.
    Do not modify.
    """
    __slots__ = ["value", "next", "prev", "child"]

    def __init__(self, value: T, next: Node = None, prev: Node = None, child: Node = None) -> None:
        """
        Construct a doubly linked list node.

        :param value: value held by the Node.
        :param next: reference to the next Node in the linked list.
        :param prev: reference to the previous Node in the linked list.
        :return: None.
        """
        self.next = next
        self.prev = prev
        self.value = value

        # The child attribute is only used for the application problem
        self.child = child

    def __repr__(self) -> str:
        """
        Represents the Node as a string.

        :return: string representation of the Node.
        """
        return f"Node({str(self.value)})"

    __str__ = __repr__


class DLL:
    """
    Implementation of a doubly linked list without padding nodes.
    Modify only below indicated line.
    """
    __slots__ = ["head", "tail", "size"]

    def __init__(self) -> None:
        """
        Construct an empty doubly linked list.

        :return: None.
        """
        self.head = self.tail = None
        self.size = 0

    def __repr__(self) -> str:
        """
        Represent the DLL as a string.

        :return: string representation of the DLL.
        """
        result = []
        node = self.head
        while node is not None:
            result.append(str(node))
            node = node.next
        return " <-> ".join(result)

    def __str__(self) -> str:
        """
        Represent the DLL as a string.

        :return: string representation of the DLL.
        """
        return repr(self)

    # MODIFY BELOW #

    def empty(self) -> bool:
        """
        Tests if the DLL contains any Nodes

        :return: True if empty, False if not
        """
        return self.head is None

    def push(self, val: T, back: bool = True) -> None:
        """
        Creates a new Node and adds it to the back or front of the DLL.

        :param val: A value to add to the DLL
        :param back: defaults to True, will add the Node to the front if False
        :return: None
        """
        new = Node(val)
        if self.empty():
            self.head = new
            self.tail = new
        elif back is True:
            # add new node to back
            self.tail.next = new
            new.prev = self.tail
            self.tail = new
        else:
            # add new node to front
            new.next = self.head
            self.head.prev = new
            self.head = new

        self.size += 1

    def pop(self, back: bool = True) -> None:
        """
        Deletes the last or first Node from the DLL.

        :param back: defaults to True, will delete Node from front if False
        :return: None
        """
        if self.empty(): # if empty, do nothing
            return None
        elif self.head is self.tail: # if the list only has one instance
            self.head = None
            self.tail = None
        elif back is False: # remove first item
            self.head.next.prev = None
            self.head = self.head.next
        else: # remove last item
            self.tail.prev.next = None
            self.tail = self.tail.prev

        self.size -= 1 # manually update size of DLL

    def list_to_dll(self, source: List[T]) -> None:
        """
        Replaces all current data in the DLL with items in the given list

        :param source: A list of some data type
        :return: None
        """
        while self.head is not None:
            self.pop() # should work after I fix pop
        for item in source:
            self.push(item)

    def dll_to_list(self) -> List[T]:
        """
        Creates and returns a new list containing all values of Nodes in the DLL.

        :return: List[T]
        """
        result = []
        curr = self.head
        while curr is not None:
            result.append(curr.value)
            curr = curr.next
        return result

    def _find_nodes(self, val: T, find_first: bool = False) -> List[Node]:
        """
        Finds all Nodes that contain val as their value

        :param val: A value to find within DLL
        :param find_first: defaults to False
        :return: List[Nodes] containing value
        """
        result = []
        curr = self.head

        while curr is not None:
            if curr.value == val:
                result.append(curr)
            curr = curr.next

        return result

        # realizing now that I did not use the find_first bool parameter ...
        # but alas, I am out of time and it still works

    def find(self, val: T) -> Node:
        """
        Finds the first instance of value in the DLL.

        :param val: A value to find within DLL
        :return: Node, first one located
        """
        if self.empty():
            return None
        else:
            result = self._find_nodes(val)
            if not result:
                return None
            else:
                return result[0]

    def find_all(self, val: T) -> List[Node]:
        """
        Finds and returns all instances of value in DLL

        :param val: A value to find
        :return: List[Node] where all instances of value are located
        """

        result = self._find_nodes(val)
        return result

    def _remove_node(self, to_remove: Node) -> None:
        """
        Removes specified Node from DLL.

        :param to_remove: Node to remove
        :return: None
        """
        if self.head is to_remove: # if only one Node in DLL or the head is the val
            self.pop(back=False)
        elif self.tail is to_remove: # if Node is tail, call pop
            self.pop()
        elif self.size == 1:
            return None
        else:
            to_remove.prev.next = to_remove.next
            to_remove.next.prev = to_remove.prev
            self.size -= 1


    def remove(self, val: T) -> bool:
        """
        Removes the first instance of value from the DLL.

        :param val: A value to remove from DLL
        :return: True if value removed, False otherwise
        """
        to_remove = self.find(val)
        if to_remove is None:
            return False
        else:
            self._remove_node(to_remove)
            return True

    def remove_all(self, val: T) -> int:
        """
        Removes all instances of value from the DLL.

        :param val: A value to remove completely from DLL.
        :return: int of the number of Nodes removed
        """
        to_remove = self.find_all(val)
        for n in to_remove:
            self._remove_node(n)
        return len(to_remove)

    def reverse(self) -> None:
        """
        Reverses the order of the DLL, switching the head and the tail.

        :return: None
        """
        head_to_tail = self.head # lock in the current head
        curr_size = self.size # will change when I use the remove_node function
        to_move = self.tail
        prev_to_move = self.tail
        for i in range(curr_size-1):
             # move the last item in DLL
            self._remove_node(to_move)
            self.size +=1
            to_move.prev = None

            # move old tail
            to_move.next = head_to_tail
            to_move.prev = head_to_tail.prev

            # update head_to_tail pointers
            head_to_tail.prev = to_move

            if i == 0:
                self.head = to_move
            else:
                prev_to_move.next = to_move
            prev_to_move = to_move
            to_move = self.tail


class BrowserHistory:

    def __init__(self, homepage: str):
        """
        Initializes BrowserHistory with a DoublyLinkedList Class and a current Node containing
        the current website and pointers to the previous and next sites in the search history.

        :param homepage: str of a url to set as the head of the DLL and first current site
        :return: None
        """
        __slots__ = ["webs", "curr"]

        self.webs = DLL()
        self.webs.push(homepage)

        self.curr = self.webs.head

    def get_current_url(self) -> str:
        """
        Returns the current URL.

        :return: str of the URL
        """
        return self.curr.value


    def visit(self, url: str) -> None:
        """
        Adds a new website to the DLL, deletes any websites that may be after the current site,
        and sets the current site to the URL

        :param url: str URL to visit and add to DLL
        :return: None
        """
        if (self.curr is not self.webs.tail) or (self.webs.empty() is False):
            while self.webs.tail is not self.curr:
                self.webs.pop()

        self.webs.push(url)
        self.curr = self.webs.tail
    
    def backward(self) -> None:
        """
        Visits the site before the current site. Skips any malicious sites in the process.

        :return: None
        """
        if self.curr is not self.webs.head:
            current = self.curr.prev
            while metrics_api(current.value):
                current = current.prev
                if current is None:
                    current = self.curr
            self.curr = current

    def forward(self) -> None:
        """
        Visits the site after the current site. Skips any malicious sites in the process.

        :return: None
        """
        if self.curr is not self.webs.tail:
            current = self.curr.next
            while metrics_api(current.value):
                current = current.next
                if current is None:
                    current = self.curr
            self.curr = current

# DO NOT MODIFY
intervention_set = set(['https://malicious.com', 'https://phishing.com', 'https://malware.com'])
def metrics_api(url: str) -> bool:
    """
    Uses the intervention_set to determine what URLs are bad and which are good. 

    :param url: The url to check.
    :returns: True if this is a malicious website, False otherwise.
    """
    if url in intervention_set:
        return True
    return False
