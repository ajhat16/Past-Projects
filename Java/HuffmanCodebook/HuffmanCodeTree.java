public class HuffmanCodeTree {
    private HuffmanNode root;

    /**
     * One of the two constructors for the HuffmanCodeTree class. This constructor is for setting the root node of the class.
     * @param root the root node of the tree
     */
    public HuffmanCodeTree(HuffmanNode root) {
        this.root = root;
    }

    /**
     * This is the second of the two constructors for the HuffmanCodeTree class. This constructor creates a new tree using the given parameter
     * @param codebook the codebook of the tree that will be made
     */
    public HuffmanCodeTree(HuffmanCodeBook codebook) {
        String retVal = codebook.loopOver();
        root = new HuffmanNode(null, null);
        for (int i = 0; i < retVal.length(); i++) {
            put(codebook.getSequence(retVal.charAt(i)), retVal.charAt(i));
        }
    }

    /**
     * This function checks if a tree is in the valid format or not. The valid format for the tree is either internal
     * nodes that store no data and have 2 children, or leaf nodes that have no children, but store data.
     * @return true if in the valid format, false otherwise
     */
    public boolean isValid() {
        return root.isValid();
    }

    /**
     * This function adds a letter to the tree by following the variable seq in the parameter.
     * @param seq the specified sequence the letter should follow to be put into the tree
     * @param letter the letter that will be put into the tree
     */
    public void put(BinarySequence seq, char letter) {
        HuffmanNode currNode = root;
        int count = 0;
        for (boolean b : seq) {
            if (!b) {
                if (currNode.getZero() == null) {
                    currNode.setZero(new HuffmanNode(null, null));
                }
                currNode = currNode.getZero();
            } else {
                if (currNode.getOne() == null) {
                    currNode.setOne(new HuffmanNode(null, null));
                }
                currNode = currNode.getOne();
            }
            count++;

            if (count == seq.size()) {
                currNode.setData(letter);
            }
        }
    }

    /**
     * This function is used to decode a binary sequence into a String format
     * @param s the binary sequence that will be decoded
     * @return the string of the decoded binary sequence
     */
    public String decode(BinarySequence s) {
        HuffmanNode node = root;
        StringBuilder retVal = new StringBuilder();
        for (boolean b : s) {
            if (!b) {
                node = node.getZero();
            } else {
                node = node.getOne();
            }
            if (node.isLeaf()) {
                retVal.append(node.getData());
                node = root;
            }

        }
        return retVal.toString();
    }
}
