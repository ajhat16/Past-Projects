public class HuffmanNode {
    private HuffmanNode zero, one;
    private Character data;
    private boolean retVal;

    /**
     * This constructor is used for creating internal nodes for the tree. Internal nodes, in this case, store no data,
     * and reference 2 children
     * @param zero the left child of the node
     * @param one the right child of the node
     */
    public HuffmanNode(HuffmanNode zero, HuffmanNode one) {
        this.zero = zero;
        this.one = one;
        data = null;
    }

    /**
     * This constructor is used for making leaf nodes for the tree. Leaf nodes, in this case, store data, but have
     * no children.
     * @param data the data of the leaf node
     */
    public HuffmanNode(char data) {
        this.data = data;
        zero = null;
        one = null;
    }

    /**
     * This function is used for getting the 'zero' child (left child) of a node
     * @return the left child of the node
     */
    public HuffmanNode getZero() {
        return zero;
    }

    /**
     * This function is used for setting the zero child (left child) of a node
     * @param zero the value of the child that will be set
     */
    public void setZero(HuffmanNode zero) {
        this.zero = zero;
    }

    /**
     * This function is used for getting the one child (right child) of a node
     * @return the right child of the node
     */
    public HuffmanNode getOne() {
        return one;
    }

    /**
     * This function is used to set the one child (right child) of a node
     * @param one the value of the child that will be set
     */
    public void setOne(HuffmanNode one) {
        this.one = one;
    }

    /**
     * This function is used for getting the data associated with a node
     * @return the data associated with the node that called this method
     */
    public Character getData() {
        return data;
    }

    /**
     * This function is used to set the data of a node
     * @param data the value of the data that will be set
     */
    public void setData(char data) {
        this.data = data;
    }

    /**
     * This function checks if a node is a leaf or not by counting its number of children.
     * @return if the node has 0 children, true is returned. otherwise, returns false
     */
    public boolean isLeaf() {
        return zero == null && one == null;
    }

    /**
     * This function checks if every node in a tree is valid or not. A valid node is either an internal node with
     * no data and 2 children not set to null, or a leaf node with data and no children
     * @return true if every node is valid, false if at least one node is invalid
     */
    public boolean isValid() {
        if (this.data == null) {
            if (this.zero != null && this.one != null) {
                retVal = zero.isValid();
                if (!retVal) {
                    return false;
                }
                retVal = one.isValid();
                if (!retVal) {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            retVal = (this.zero == null && this.one == null);
        }
        return retVal;
    }
}
