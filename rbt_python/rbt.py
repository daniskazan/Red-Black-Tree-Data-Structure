class TreeNode:

    def __init__(self, value, parent: TreeNode,  left: TreeNode, right: TreeNode, color=None):
        self.value = value
        self.parent = parent
        self.left = None
        self.right = None
        self.color = color


class RBTree:
    def __init__(self, value, color):
        self.value = value
        self.color = "BLACK"
    
    def insert(root: TreeNode, value):
        pass


    def search(root: TreeNode, key):
        while root != None:
            if key == root.value:
                return True
            
            elif key < root.value:
                root = root.left
            
            elif key > root.value:
                root = root.right
        
        return False
    

