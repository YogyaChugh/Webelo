# Children

Hi !! This file explains how we have stored the children of any node.
So every node has a NodeList object named ChildNodes that contains the immediate children of the node, i.e. all nodes whose parent is that node.
Now, as we store them in childNodes, those nodes further point to their children which forms a whole chain till the point where the childNodes is empty !!

You can think of it like this:

```html
<div>
    <a href="www.google.com"> Google </a>
    <h1> Hello </h1>
    <div>
        <h2>Hello again !!</h2>
    </div>
</div>
```
Here, the first div got 3 children a, h1 and div and further div got h2 as its child.

## Parsing
So when we say whether something is a descendant or sibling, etc.. we do it based on the pre-order Depth First Search algorithm.
The algorithm tends to follow each child to it's depth before moving to it's sibling.
First, the root,i.e. parent is visited then the left child and finally when all kids of the left child are visited, we march our way to do the same with right child !
But since our implementation ain't a simple BST, we got multiple children not restricting to just left and right. Therefore, we move in the order of left to right !!

> Yup ! That's it, simple af