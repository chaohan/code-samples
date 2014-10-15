/**
 *  Binary Node
 *  @author Alex Han
 */

public class Node
{
      private Comparable key;
      private Object value;
      private boolean isRed = false;
      
      public Node right = null;
      public Node left  = null;
      
      public Node(Comparable key)
      {
            this.key = key;
            this.value = null;
      }
      
      public Node(Comparable key, Object value)
      {
            this.key = key;
            this.value = value;
      }
      
      public boolean isRed()
      { return isRed; }
      
      public void flipColor()
      { isRed = !isRed; }
      
      public Comparable getKey()
      { return key; }

      public Object getValue()
      { return value; }

      public void setKey(Comparable newKey)
      { this.key = newKey; }
      
      public void setValue(Object newValue)
      { this.value = newValue; }

      public static void main(String[] args)
      {
            Node my_node  = new Node(0.0);
            my_node.flipColor();
            System.out.println("color is red?"+my_node.isRed());
            System.out.println("key="+my_node.getKey());
            System.out.println("value="+my_node.getValue());
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
