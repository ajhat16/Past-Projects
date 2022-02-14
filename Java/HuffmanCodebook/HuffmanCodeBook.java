public class HuffmanCodeBook {
    private MyBinarySearchTree<Character> characters;

    public static class MyBinarySearchTree<T extends Comparable<T>> {
        public static class MyBSTNode<T> {
            private MyBSTNode<T> left;
            private MyBSTNode<T> right;
            private T data;
            private BinarySequence sequence;

            /**
             * Constructor for the MyBSTNode class. This constructor initializes the data and sequence variables
             * @param data the data you would like to initialize data to. This variable is of type T (generic)
             * @param seq the sequence you would like to initialize sequence to. This variable is of type BinarySequence
             */
            public MyBSTNode(T data, BinarySequence seq) {
                this.data = data;
                this.sequence = seq;
            }

            /**
             * This function sets the data of a node to the parameter data
             * @param data the variable that data will be set to
             */
            public void setData(T data) {
                this.data = data;
            }

            /**
             * This function is used to access the information that data is storing
             * @return the data variable
             */
            public T getData() {
                return data;
            }

            /**
             * This function sets the left child of a node to the parameter left
             * @param left the node that left will be set to
             */
            public void setLeft(MyBSTNode<T> left) {
                this.left = left;
            }

            /**
             * This function sets the right child of a node to the parameter right
             * @param right the node that right will be set to
             */
            public void setRight(MyBSTNode<T> right) {
                this.right = right;
            }

            /**
             * This function is used to get the left child of the node that calls it
             * @return the left child of a node
             */
            public MyBSTNode<T> getLeft() {
                return left;
            }

            /**
             * This function is used to get the right child of the node that calls it
             * @return the right child of a node
             */
            public MyBSTNode<T> getRight() {
                return right;
            }

            /**
             * This function is used to get the sequence of a node
             * @return the sequence of a node
             */
            public BinarySequence getSequence() {
                return sequence;
            }

            /**
             * This function is used to set the sequence of a node to the parameter sequence
             * @param sequence the variable that sequence will be set to
             */
            public void setSequence(BinarySequence sequence) {
                this.sequence = sequence;
            }

            /**
             * This function overwrites the toString function to give data as a string
             * @return data as a string
             */
            @Override
            public String toString() {
                return String.valueOf(data);
            }
        }

        private MyBSTNode<T> root;

        /**
         * This function is the constructor for the MyBinarySearchTree class. This function takes no parameters, and sets root to null (making an empty tree)
         */
        public MyBinarySearchTree() {
            root = null;
        }

        /**
         * This function is a helper function for the private add function. This function exists to make sure that the private add function always starts at the root of the BST
         * @param data the data of the node that will be added
         * @param sequence the sequence of the node that will be added
         */
        public void add(T data, BinarySequence sequence) {
            add(this.root, data, sequence);
        }

        /**
         * A recursive function that traverses the BST searching for the correct place to add the new node based on the data variable.
         * @param tree the current node that the function will use to compare data. This will allow the new node to be put in the right place
         * @param data the data that the new node will be set to
         * @param sequence the sequence that the new node will be set to
         */
        private void add(MyBSTNode<T> tree, T data, BinarySequence sequence) {
            if (tree == null) {
                root = new MyBSTNode<>(data, sequence);
            } else if (tree.getData().compareTo(data) == 0) {
                return;
            } else if (tree.getData().compareTo(data) > 0 && tree.getLeft() != null) {
                add(tree.getLeft(), data, sequence);
            } else if (tree.getData().compareTo(data) > 0 && tree.getLeft() == null) {
                tree.setLeft(new MyBSTNode<>(data, sequence));
            } else if (tree.getData().compareTo(data) < 0 && tree.getRight() != null) {
                add(tree.getRight(), data, sequence);
            } else if (tree.getData().compareTo(data) < 0 && tree.getRight() == null) {
                tree.setRight(new MyBSTNode<>(data, sequence));
            }
        }

        /**
         * This function is a helper function for the private contains function. This function ensures that the private contains function always starts at the root of the BST
         * @param data the data that will be searched for
         * @return the result of the private contains method: either true if it is in the BST, or false if it is not
         */
        public boolean contains(T data) {
            return contains(this.root, data);
        }

        /**
         * This recursive function is the private contains function. This function searches the BST for data, starting at the root
         * @param tree the node that will be compared to data
         * @param data the data that we are searching for
         * @return true if it is in the BST, false otherwise
         */
        private boolean contains(MyBSTNode<T> tree, T data) {
            if (tree == null) {
                return false;
            }
            else {
                if (tree.getData() != null && tree.getData().compareTo(data) > 0) {
                    return contains(tree.getLeft(), data);
                } else if (tree.getData() != null && tree.getData().compareTo(data) < 0) {
                    return contains(tree.getRight(), data);
                }
                return true;
            }
        }

        /**
         * This function is a helper function for the private get function. This function ensures that the private get function will start at the root node
         * @param data the data we would like to access the node of
         * @return the result of the private get method: the node if it exists in the BST, otherwise it returns null
         */
        public MyBSTNode<T> get(T data) {
            return get(root, data);
        }

        /**
         * This recursive function is used get the node associated with data.
         * @param tree the node that will be used to compare to data in order to go down the correct branch in the tree. This should start at root
         * @param data the data we would like to get the node of
         * @return the node associated with data, otherwise returns null
         */
        private MyBSTNode<T> get(MyBSTNode<T> tree, T data) {
            if (tree == null) {
                return null;
            } else {
                if (tree.getData().compareTo(data) > 0) {
                    return get(tree.getLeft(), data);
                } else if (tree.getData().compareTo(data) < 0) {
                    return get(tree.getRight(), data);
                }
                return tree;
            }
        }

        /**
         * This is a recursive helper function for the remove function. This function keeps going left in the tree until it finds null
         * @param tree the node you are searching left from
         * @return the last node going left from tree
         */
        private MyBSTNode<T> searchLeft (MyBSTNode<T> tree) {
            while (tree.getLeft() != null) {
                tree = tree.getLeft();
            }
            return tree;
        }

        /**
         * This function loops through the tree searching for the parent of the node associated with data. This is a helper function for the remove function
         * @param data the data associated with the node we would like to find the parent of
         * @return the parent of the node associated with data
         */
        private MyBSTNode<T> findParent(T data) {
            MyBSTNode<T> parent = root;
            while (parent != null) {
                if (parent.getLeft() != null) {
                    if (parent.getLeft().getData().equals(data)) {
                        break;
                    }
                }
                if (parent.getRight() != null) {
                    if (parent.getRight().getData().equals(data)) {
                        break;
                    }
                }
                if (parent.getData().compareTo(data) > 0) {
                    parent = parent.getLeft();
                } else if (parent.getData().compareTo(data) < 0) {
                    parent = parent.getRight();
                }
            }
            return parent;
        }

        /**
         * This is a recursive helper function for the remove method. This function keeps going right in the tree until it finds null
         * @param tree the node you are searching right from
         * @return the last node going right from the tree
         */
        private MyBSTNode<T> searchRight(MyBSTNode<T> tree) {
            while (tree.getRight() != null) {
                tree = tree.getRight();
            }
            return tree;
        }

        /**
         * This is a helper function for remove that ensures remove always starts at the root node.
         * @param data the data associated with the node we would like to remove
         */
        public void remove(T data) {
            remove(root, data);
        }

        /**
         * This function removes the node associated with data. It is a helper function for the remove function to make remove easier to read.
         * @param tree the node associated with the data that we want to remove
         * @param data the data of the node that we want to remove
         */
        private void doRemove(MyBSTNode<T> tree, T data) {
            MyBSTNode<T> parent;
            if (tree.equals(root)) {
                if (tree.getLeft() == null && tree.getRight() == null) {
                    root.setData(null);
                    root.setSequence(null);
                } else if (tree.getLeft() != null && tree.getRight() == null) {
                    MyBSTNode<T> currNode = tree.getLeft();
                    if (currNode.getRight() == null) {
                        tree.setData(currNode.getData());
                        tree.setLeft(currNode.getLeft());
                    } else {
                        currNode = searchRight(currNode);
                        parent = findParent(currNode.getData());
                        tree.setData(currNode.getData());
                        parent.setRight(currNode.getLeft());
                        currNode.setData(null);
                    }
                }  else if (tree.getRight() != null && tree.getLeft() == null) {
                    MyBSTNode<T> currNode = tree.getRight();
                    if (currNode.getLeft() == null) {
                        tree.setData(currNode.getData());
                        tree.setRight(currNode.getRight());
                    } else {
                        currNode = searchLeft(currNode);
                        parent = findParent(currNode.getData());
                        tree.setData(currNode.getData());
                        parent.setLeft(currNode.getRight());
                        currNode.setData(null);
                    }
                    //parent.setRight(null);
                } else if (tree.getRight() != null && tree.getLeft() != null) {
                    MyBSTNode<T> currNode = tree.getRight();
                    if (currNode.getLeft() == null) {
                        tree.setData(currNode.getData());
                        tree.setRight(currNode.getRight());
                    } else {
                        currNode = searchLeft(currNode);
                        parent = findParent(currNode.getData());
                        tree.setData(currNode.getData());
                        parent.setLeft(currNode.getRight());
                        currNode.setData(null);
                    }
                }
            } else {
                parent = findParent(data);
                if (tree.getLeft() == null && tree.getRight() == null) {
                    if (parent.getLeft() != null && parent.getLeft().getData().equals(data)) {
                        parent.setLeft(null);
                    } else if (parent.getRight() != null && parent.getLeft().getData().equals(data)) {
                        parent.setRight(null);
                    }
                    tree.setData(null);
                    tree.setSequence(null);
                    //Pseudocode:
                    //else if 1 child is left child, go right then left until you find null
                    //else if 1 child is right child, go left then right until you find null
                    //else if 2 children, go right then left until you find null
                } else if (tree.getLeft() != null && tree.getRight() == null) {
                    MyBSTNode<T> currNode = tree.getLeft();
                    if (currNode.getRight() == null) {
                        tree.setData(currNode.getData());
                        tree.setLeft(currNode.getLeft());
                    } else {
                        currNode = searchRight(currNode);
                        parent = findParent(currNode.getData());
                        tree.setData(currNode.getData());
                        parent.setRight(currNode.getLeft());
                        currNode.setData(null);
                    }
                    //parent.setLeft(null);
                } else if (tree.getRight() != null && tree.getLeft() == null) {
                    MyBSTNode<T> currNode = tree.getRight();
                    if (currNode.getLeft() == null) {
                        tree.setData(currNode.getData());
                        tree.setRight(currNode.getRight());
                    } else {
                        currNode = searchLeft(currNode);
                        parent = findParent(currNode.getData());
                        tree.setData(currNode.getData());
                        parent.setLeft(currNode.getRight());
                        currNode.setData(null);
                    }
                    //parent.setRight(null);
                } else if (tree.getRight() != null && tree.getLeft() != null){
                    MyBSTNode<T> currNode = tree.getRight();
                    if (currNode.getLeft() == null) {
                        tree.setData(currNode.getData());
                        tree.setRight(currNode.getRight());
                    } else {
                        currNode = searchLeft(currNode);
                        parent = findParent(currNode.getData());
                        tree.setData(currNode.getData());
                        parent.setLeft(currNode.getRight());
                        currNode.setData(null);
                    }
                }
            }
        }

        /**
         * This function will search for the node associated with data starting at the root, then removes the node associated with data. It does nothing if data is not present in the function
         * @param tree the node we are comparing to data, and the node we are removing
         * @param data the data associated with the node we would like ti remove
         */
        private void remove(MyBSTNode<T> tree, T data) {
            MyBSTNode<T> parent;
            if (tree == null) {
                return;
            } else {
                //No children, 1 child, 2 children
                if (tree.getData().compareTo(data) > 0) {
                    remove(tree.getLeft(), data);
                } else if (tree.getData().compareTo(data) < 0) {
                    remove(tree.getRight(), data);
                } else if (tree.getData().compareTo(data) == 0) {
                    doRemove(tree, data);
                    /*parent = findParent(data);
                    if (tree.getLeft() == null && tree.getRight() == null) {
                        if (parent.getLeft() != null && parent.getLeft().getData().equals(data)) {
                            parent.setLeft(null);
                        } else if (parent.getRight() != null && parent.getLeft().getData().equals(data)) {
                            parent.setRight(null);
                        }
                        tree.setData(null);
                        tree.setSequence(null);
                    //Pseudocode:
                    //else if 1 child is left child, go right then left until you find null
                    //else if 1 child is right child, go left then right until you find null
                    //else if 2 children, go right then left until you find null
                    } else if (tree.getLeft() != null && tree.getRight() == null) {
                        MyBSTNode<T> currNode = tree.getLeft();
                        if (currNode.getRight() == null) {
                            tree.setData(currNode.getData());
                            tree.setLeft(currNode.getLeft());
                        } else {
                            currNode = searchRight(currNode);
                            parent = findParent(currNode.getData());
                            tree.setData(currNode.getData());
                            parent.setRight(currNode.getLeft());
                            currNode.setData(null);
                        }
                        //parent.setLeft(null);
                    } else if (tree.getRight() != null && tree.getLeft() == null) {
                        MyBSTNode<T> currNode = tree.getRight();
                        if (currNode.getLeft() == null) {
                            tree.setData(currNode.getData());
                            tree.setRight(currNode.getRight());
                        } else {
                           currNode = searchLeft(currNode);
                           parent = findParent(currNode.getData());
                           tree.setData(currNode.getData());
                           parent.setLeft(currNode.getRight());
                           currNode.setData(null);
                        }
                        parent.setRight(null);
                    } else if (tree.getRight() != null && tree.getLeft() != null){
                        MyBSTNode<T> currNode = tree.getRight();
                        if (currNode.getLeft() == null) {
                            tree.setData(currNode.getData());
                            tree.setRight(currNode.getRight());
                        } else {
                            currNode = searchLeft(currNode);
                            parent = findParent(currNode.getData());
                            tree.setData(currNode.getData());
                            parent.setLeft(currNode.getRight());
                            currNode.setData(null);
                        }
                    }*/
                }
            }
        }

        /**
         * This is a helper function for the loopInOrder function that ensures loopInOrder always starts looping from the root.
         * @return a string containing all data in the tree
         */
        public String loopInOrder() {
            return loopInOrder(root, "");
        }

        /**
         * This function loops through the BST in order, storing each data point in the string retVal
         * @param tree the node that holds the data that will be added to retval
         * @param retVal a string storing all data in the BST as a string
         * @return a string containing all data in the tree (retVal)
         */
        private String loopInOrder(MyBSTNode<T> tree, String retVal) {
            if (tree != null) {
                retVal = loopInOrder(tree.getLeft(), retVal);
                retVal += tree;
                retVal = loopInOrder(tree.getRight(), retVal);
            }
            return retVal;
        }

        /**
         * This function overwrites the toString method to create a string for the BST
         * @return a string containing all data in the tree (the return value of loopInOrder)
         */
        @Override
        public String toString() {
            return loopInOrder();
        }
    }

    /**
     * Constructor for the HuffmanCodeBook class. This constructor initializes the characters and sequences array lists
     */
    public HuffmanCodeBook() {
        characters = new MyBinarySearchTree<>();
    }

    /**
     * This function uses the MyBinarySearchTree loopOver function to loop over the data in the tree in order,
     * and store the values in a string
     * @return a string storing all data from the binary search tree
     */
    public String loopOver() {
        return characters.loopInOrder();
    }

    /**
     * This function adds a character and a sequence to characters and sequences respectively.
     * @param c the character seq is associated with
     * @param seq the sequence that will be added
     */
    public void addSequence (char c, BinarySequence seq) {
        characters.add(c, seq);
    }

    /**
     * This function checks if characters contains a specific character
     * @param letter the character we are searching for
     * @return true if the character is in the array list, false otherwise
     */
    public boolean contains(char letter) {
        return characters.contains(letter);
    }

    /**
     * Checks characters to see if every character represented in letters is in the array list
     * @param letters the letters we are searching for
     * @return true if every character is present in characters, false otherwise
     */
    public boolean containsAll(String letters) {
        for (int i = 0; i < letters.length(); i++) {
            if (!characters.contains(letters.charAt(i))) {
                return false;
            }
        }
        return true;
    }

    /**
     * This function gets the sequence associated with the character c
     * @param c the character we are searching for the sequence of
     * @return the sequence associated with c
     */
    public BinarySequence getSequence(char c) {
        MyBinarySearchTree.MyBSTNode<Character> character = characters.get(c);
        if (character == null) {
            return null;
        } else {
            return character.getSequence();
        }
    }

    /**
     * This function converts a string into an encoded BinarySequence message
     * @param s the string we would like to encode
     * @return the binary sequence of each character in the string
     */
    public BinarySequence encode(String s) {
        BinarySequence seq = new BinarySequence();

        for (int i = 0; i < s.length(); i++) {
            seq.append(characters.get(s.charAt(i)).getSequence());
        }
        return seq;
    }

    /*public static void main(String[] args) {
        System.out.println(ProvidedHuffmanCodeBook.getEbookHuffmanCodebook().contains('e'));
        System.out.println(ProvidedHuffmanCodeBook.getEbookHuffmanCodebook().containsAll("e a"));
        System.out.println(ProvidedHuffmanCodeBook.getEbookHuffmanCodebook().getSequence('e'));
        System.out.println(ProvidedHuffmanCodeBook.getEbookHuffmanCodebook().encode("test"));
        MyLinkedList<Character> test = new MyLinkedList<>();
        test.append('a');
        test.append('e');
        test.append('i');
        System.out.println(test.remove(1));
        System.out.println(test.removeHead());
        System.out.println(test.removeTail());
        System.out.println(test.getLength());
    }*/
}
