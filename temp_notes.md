let there be a stack

some_recursive_fun(element){
    if element.has_children {
        stack.append(self)
        for (each child of the element){
            some_recursive_func(child)
        }
    }
}
while stack is not empty {