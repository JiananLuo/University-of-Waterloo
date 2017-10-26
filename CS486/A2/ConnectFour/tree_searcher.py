class Node:
    """
    Representation of a generic game tree node.
    Each node holds
    1. a label
    2. a static value (internal nodes
    generally have a None static value)
    3. node type  {MIN, MAX}
    4. list of child nodes.
    """
    def __init__(self, label, value, node_type, children=None):
        if children is None:
            children = []

        self.label = label
        self.value = value
        self.node_type = node_type
        self.children = children
    
    def set_children(self, child_nodes):
        """
        Set the children of this tree node
        """
        if not self.children:
            self.children = []
        for child in child_nodes:
            self.children.append(child)

    def get_children(self):
        return self.children
    
    def __str__(self):
        """
        Print the value of this node.
        """
        if self.value is None:
            return self.label
        else:
            return "{}[{}]".format(self.label, self.value)
    
    def add(self, child):
        """
        Add children to this node.
        """
        if not self.children:
            self.children = []
        self.children.append(child)

    def num_children(self):
        """
        Find how many children this node has.
        """
        if self.children:
            return len(self.children)
        else:
            return 0


def tree_as_string(node, depth=0):
    """
    Generates a string representation of the tree
    in a space indented format
    """
    static_value = tree_eval(node)
    buf = "{}{}:{}\n".format(" "*depth, node.label, static_value)
    for elt in node.children:
        buf += tree_as_string(elt, depth+1)
    return buf


def make_tree(tup):
    """
    Generates a Node tree from a tuple formatted tree
    """
    return make_tree_helper(tup, "MAX")


def make_tree_helper(tup, node_type):
    """
    Generate a Tree from tuple format
    """
    n = Node(tup[0], tup[1], node_type)
    children = []
    if len(tup) > 2:
        if node_type == "MAX":
            node_type = "MIN"
        else:
            node_type = "MAX"
        
    for c in range(2,len(tup)):
        children.append(make_tree_helper(tup[c], node_type))
    n.set_children(children)
    return n


def is_at_depth(depth, node):
    """
    is_terminal_fn for fixed depth trees
    True if depth == 0 has been reached.
    """
    return depth <= 0


def is_leaf(depth, node):
    """
    is_terminal_fn for variable-depth trees.
    Check if a node is a leaf node.
    """
    return node.num_children() == 0


def tree_get_next_move(node):
    """
    get_next_move_fn for trees
    Returns the list of next moves for traversing the tree
    """
    return [(n.label, n) for n in node.children]


def tree_eval(node):
    """
    Returns the static value of a node
    """
    if node.value is None:
        return None

    if node.node_type == "MIN":
        return -node.value
    elif node.node_type == "MAX":
        return node.value
    else:
        raise Exception("Unrecognized node type: {}".format(node.node_type))
