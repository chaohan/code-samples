/**
 *  Binary Node
 *  @author Alex Han
 */

public class Node <keyType extends Comparable, valueType>
{
      private keyType key;
      private valueType value;
      private boolean isRed = false;
      
      public Node right = null;
      public Node left  = null;
      
      public Node(keyType newKey)
      {
            key = newKey;
            value = null;
      }
      
      public Node(keyType newKey, valueType newValue)
      {
            key = newKey;
            value = newValue;
      }
      
      public boolean isRed()
      { return isRed; }
      
      public void flipColor()
      { isRed = !isRed; }
      
      public keyType getKey()
      { return key; }

      public valueType getValue()
      { return value; }

      public void setKey(keyType newKey)
      { key = newKey; }
      
      public void setValue(valueType newValue)
      { value = newValue; }

      public static void main(String[] args)
      {
            Node<Integer,Integer> my_node  = new Node<>(0);
            my_node.flipColor();
            System.out.println("check color=red is true:"+my_node.isRed());
            System.out.println("check key=0:"+my_node.getKey());
            System.out.println("check value=null"+my_node.getValue());
      }
}






/*public void print_chain()
 {
 Node j = this;
 while(j.next!=null)
 {
 System.out.print("("+j.key+":"+j.value+")"+"->");
 j = j.next;
 }
 System.out.println();
 }
 */


/*
 Node new_node = my_node;
 for (int j=1;j<10;j++)
 {
 new_node.add_next(new Node("new",j));
 new_node = new_node.next;
 }
 */
