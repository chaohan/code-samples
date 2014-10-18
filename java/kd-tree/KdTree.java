/**
      2D Tree
 
      Each node of the tree is implemented using a Node (originally 
      intended for a red-black BST).
 
      The key of each node is a Point2D object, the value of each node is a
      RectHV object, representing the rectangle the point is bisecting.
      
      @author Alex Han
*/

public class KdTree {

      private Node<Point2D,RectHV> iterator;
      private int side;
      private Node<Point2D,RectHV> root;
      private int size;

      public KdTree() // construct an empty set of points
      { root = null; size = 0; }
            
      public boolean isEmpty() // is the set empty?
      { return size == 0; }
      
      public int size() // number of points in the set
      { return size; }
      
      public void insert(Point2D p)
      // add the point to the set (if it is not already in the set)
      {
            if (root==null) { root = new Node<>(p); size++; }
            else
            {
                  search(p);
                  if (side==-1) { iterator.left = new Node<>(p); size++; }
                  else if (side==1) { iterator.right = new Node(p); size++; }
            }
            
      }
                  
      public boolean contains(Point2D p) // does the set contain point p?
      {
            if (root==null) { return false; }
            else { search(p); return side==0; }
      }
      
/**   
      a helper method, when terminates: for non-existing point, "iterator" is at 
      the parent node to the correct position to inser it, and "side" indicates 
      left (-1) or right(1) to the parent node. for an existing node, "iterator" 
      is at the correct searched position and side=0
 */
      private void search(Point2D newPt)
      {
            iterator = root;
            // root==null case is taken care of in methods using this method
            boolean goLeft;
            boolean compareX = true;
            while (true)
            {
                  Point2D current = iterator.getKey();
                  
                  if (compareX) { goLeft = ( newPt.x() < current.x() ); }
                  else { goLeft = ( newPt.y() < current.y() ); }
                        
                  if (goLeft)
                  {
                        if (iterator.left==null) {side=-1; break;}
                        else { iterator = iterator.left; compareX=!compareX; }
                  }
                  else
                  {
                        if(newPt.compareTo(current)==0) { side=0; break; }
                        else if (iterator.right==null) { side=1; break; }
                        else { iterator = iterator.right; compareX=!compareX; }
                  }
            }
      }
      
      public void draw() // draw all points to standard draw
      {
            
            StdDraw.setCanvasSize(500,500);
            StdDraw.square(0.5,0.5,0.5);
            
            for (int j=1;j<10;j++)
            {
                  Hline(new Point2D(0.1*((double) j),0.1*((double) j)));
            }
            
            for (int j=1;j<10;j++)
            {
                  Vline(new Point2D(0.1*((double) j),0.05*((double) j)));
            }

      }
      
      private void Hline(Point2D pt) // StdDraw a blue horizontal line
      {
            StdDraw.setPenColor(0,0,200);
            StdDraw.setPenRadius(0.01);
            StdDraw.line(0.0,pt.y(),1.0,pt.y());

            StdDraw.setPenColor(0,0,0);
            StdDraw.setPenRadius(0.02);
            StdDraw.point(pt.x(),pt.y());
      }
      
      private void Vline(Point2D pt) // StdDraw a red vertical line
      {
            StdDraw.setPenColor(200,0,0);
            StdDraw.setPenRadius(0.01);
            StdDraw.line(pt.x(),0.0,pt.x(),1.0);
            
            StdDraw.setPenColor(0,0,0);
            StdDraw.setPenRadius(0.02);
            StdDraw.point(pt.x(),pt.y());
      }
      
      public Iterable<Point2D> range(RectHV rect)
      // all points that are inside the rectangle
      {return null;}
      
      public Point2D nearest(Point2D p)
      // a nearest neighbor in the set to point p; null if the set is empty
      {return null;}
      
      public static void main(String[] args) // unit testing of the methods
      {
            KdTree newTree = new KdTree();
            for (int j=1;j<10;j++)
            {
                  newTree.insert(new Point2D(0.111*j,0.111*j));
            }
            System.out.println("points inserted:"+newTree.size());
            Node<Point2D,RectHV> iter = newTree.root;
            for (int j=1;j<10;j++)
            {
                  Point2D pt = iter.getKey();
                  System.out.println(pt.x());
                  iter = iter.right;
            }
            for (int j=1;j<10;j++)
            {
                System.out.println(newTree.contains(new Point2D(0.111*j,0.111*j)));
            }
            
      }
}