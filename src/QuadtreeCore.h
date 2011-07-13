#ifndef QUADTREE_CORE_H
#define QUADTREE_CORE_H

#include <vector>

namespace Comrade {
    namespace IrisFoundation {

template <typename Generic>
class TreeNode
{
protected:  void recursive_deallocate(TreeNode* current);

public:     Generic data;
            TreeNode* parent;
            bool terminal;
            std::vector<TreeNode*> branch_list;

            TreeNode(Generic info);

            void set_parent(TreeNode* par);
            void add_branch(Generic info);
            void set_terminal(bool status);
            void set_data(Generic info);
            bool is_terminal();

            ~TreeNode();
};

template <typename Any, typename Some>
class Tree
{
protected:  TreeNode<Any>* root;
            bool (*contains)(Any info1, Some info2);
            void recursive_get_terminals(TreeNode<Any>* current,
                                         std::vector<TreeNode<Any>*>* term_list);

            TreeNode<Any>* recursive_search(TreeNode<Any>* current,Some data);


public:     Tree(Any initial);

            TreeNode<Any>* get_root();
            void set_subsethood_fn(bool (*fn)(Any info1, Some info2));
            TreeNode<Any>* locate(Some data);
            void get_terminal_nodes(std::vector<TreeNode<Any>*>* term_list);

            ~Tree();
};


template <typename Generic>
TreeNode<Generic>::TreeNode(Generic info)
{
    data=info;
    terminal=true;
}

template <typename Generic>
void TreeNode<Generic>::set_parent(TreeNode<Generic>* par)
{
    parent=par;
}

template <typename Generic>
void TreeNode<Generic>::add_branch(Generic info)
{
    terminal=false;
    TreeNode* newnode=new TreeNode(info);
    newnode->set_parent(this);
    newnode->set_terminal(true);
    branch_list.push_back(newnode);
}

template <typename Generic>
void TreeNode<Generic>::set_terminal(bool status)
{
    if (status==true)
    {
        TreeNode* current=this;
        recursive_deallocate(current);
    }

    terminal=status;
}

template <typename Generic>
void TreeNode<Generic>::set_data(Generic info)
{
    data=info;
}

template <typename Generic>
bool TreeNode<Generic>::is_terminal()
{
    return terminal;
}

template <typename Generic>
void TreeNode<Generic>::recursive_deallocate(TreeNode* current)
{
    if (current->branch_list.size()==0)
    {
        return;
    }

    for (unsigned int i=0; i<=current->branch_list.size()-1; i++)
    {
        TreeNode* node=current->branch_list[i];

        if(node->terminal==false)
        {
            recursive_deallocate(node);
        }

        delete node;
    }
}

template <typename Generic>
TreeNode<Generic>::~TreeNode()
{}

template <typename Any, typename Some>
Tree<Any,Some>::Tree(Any initial)
{
    root=new TreeNode<Any>(initial);
}

template <typename Any, typename Some>
TreeNode<Any>* Tree<Any,Some>::get_root()
{
    return root;
}
            
template <typename Any, typename Some>
void Tree<Any,Some>::set_subsethood_fn(bool (*fn)(Any info1, Some info2))
{
    contains=fn;
}
            
template <typename Any, typename Some>
TreeNode<Any>* Tree<Any,Some>::locate(Some data)
{
    TreeNode<Any>* start=root;
    TreeNode<Any>* ans=recursive_search(start,data);

    return ans;
}

template <typename Any, typename Some>
void Tree<Any,Some>::recursive_get_terminals(TreeNode<Any>* current,
                                             std::vector<TreeNode<Any>*>* term_list)
{
    if (current->branch_list.size()==0 || current->terminal==true)
    {

        term_list->push_back(current);
        return;
    }

    for (int i=0; i<=current->branch_list.size()-1; i++)
    {
        TreeNode<Any>* node=current->branch_list[i];
        recursive_get_terminals(node,term_list);
    }
}

template <typename Any, typename Some>
TreeNode<Any>* Tree<Any,Some>::recursive_search(TreeNode<Any>* current,Some data)
{
    //cout<<"Current data is "<<current->data<<" and size="<<current->branch_list.size();
    if (current->branch_list.size()==0 || current->is_terminal()==true)
    {
        return current;
    }

    bool flag=false;
    TreeNode<Any>* candidate;

    for (int i=0; i<=current->branch_list.size()-1; i++)
    {
        if (contains(current->branch_list[i]->data,data)==true)
        {
            //cout<<"Leaving "<<current->data<<endl;

            flag=true;
            candidate=recursive_search(current->branch_list[i],data);
            break;
        }
    }

    if (flag==false)
    {
        return current;
    }

    else
    {
        return candidate;
    }
}

template <typename Any, typename Some>
void Tree<Any,Some>::get_terminal_nodes(std::vector<TreeNode<Any>*>* term_list)

{
    TreeNode<Any>* start=root;
    recursive_get_terminals(root,term_list);
}

template <typename Any, typename Some>
Tree<Any,Some>::~Tree()
{
    root->set_terminal(true);
    delete root;
}

}
}

#endif


