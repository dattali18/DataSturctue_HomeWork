class Node:
    def __init__(self, val=""):
        self.val = val
        self.child = []

    def __repr__(self) -> str:
        return f"Node({self.val})"
    


class Tree:
    def __init__(self, val=""):
        self.root = Node(val)

    def print_tree(self, node:Node):
        print(node)
        for n in node.child:
            self.print_tree(n)

    def search_rec(self, node:Node, val:str, lst:list):
        if node is None:
            return
        if node.val == val:
            lst.append(node.val)
            return

        for nd in node.child:
            self.search_rec(nd, val, lst)


    def search(self, val:str):
        lst = list()
        self.search_rec(self.root, val, lst)
        print(lst)


def main():
    tree = Tree('root')
    
    tree.root.child.append(Node('child-1'))
    tree.root.child.append(Node('child-2'))
    tree.root.child.append(Node('child-3'))

    tree.root.child[0].child.append(Node("child-1.1"))
    tree.root.child[0].child.append(Node("child-1.2"))


    tree.root.child[1].child.append(Node("child-2.1"))
    tree.root.child[1].child[0].child.append(Node("child-2.1.1"))

    tree.root.child[1].child.append(Node("child-2.2"))

    tree.root.child[1].child.append(Node("child-2.3"))
    tree.root.child[1].child[2].child.append(Node("child-2.3.1"))

    tree.print_tree(node=tree.root)

if __name__ == '__main__':
    main()
        
