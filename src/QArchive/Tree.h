#ifndef TREE_H
#define TREE_H

#include <QList>
#include <QString>
#include <QStringList>

namespace qarchive{

template <typename T>
class TreeNode;

template <typename Type>
class treeConstIterator;

template <typename Type>
class Tree
{
	TreeNode<Type> fRoot;
	TreeNode<Type>* fCurrentNode;
public:
	Tree();

	TreeNode<Type>* changeDir(QString path, bool &dirFound);
	TreeNode<Type>* changeDir(QString path){bool b; return changeDir(path,b);}
	QString			currentDir() const;
	TreeNode<Type>* upDir();
	bool			setCurrentNode(TreeNode<Type>* node);

	TreeNode<Type>* searchDir(QString path);
	bool			searchItem(QString path, Type& item);
	bool			addItem(QString name, const Type& item, bool currentDir = false);
	bool			addDir(QString path);

	treeConstIterator<Type> localIterator() const {return fCurrentNode->iterator();}
	treeConstIterator<Type> globalIterator() const {return fRoot.iterator();}

private:
	TreeNode<Type>* extractPath(QString path, QString &name);
	QString absolutePath(QString path);
};

template <typename Type>
class TreeNode
{
	friend class Tree<Type>;


	QString fName;
	QList< TreeNode<Type> > fChildren;
	QList<QPair<QString,Type> > fItems;
	TreeNode<Type>* fParent=0;
	Tree<Type>* fTree;

public:
	TreeNode(QString name):fName(name){}

	QString			 getName() const {return fName;}
	TreeNode<Type>*  parent()  const {return fParent;}

	const Type&	at(int i)	const {return fItems.at(i).second;}
	QString		nameAt(int i) const {return fItems.at(i).first;}
	int			itemCount()	const {return fItems.size();}
	bool		searchItem(QString name, Type& item) const;
	QStringList itemsNames() const;
	int			addItem(QString name, const Type& item);
	QList<QPair<QString, Type>>& items() {return fItems;}

	const TreeNode<Type>&	childAt(int i) const {return fChildren.at(i);}
	int					childrenCount()		const {return fChildren.size();}
	TreeNode<Type>*		searchChildren(QString name);
	QStringList			childrenNames()	const;
	int					childID(QString name) const;
	int					addChildren(QString name);
	QList< TreeNode<Type> >& childrenList() {return fChildren;}

	bool contains(QString name);
	TreeNode<Type>*		createPath(QString name);
	QString path() const;

	treeConstIterator<Type> iterator() const {return treeConstIterator<Type>(this);}
};

enum Movement{
	TREE_END = 0,
	BRANCH = 2,
	LEAVING_BRANCH = 3,
	ITEM = 4
};

template <typename Type>
class treeConstIterator{

	const TreeNode<Type>* fNode;
	int fPos=-1;
	bool fReadingItem=true;

public:
	treeConstIterator(const TreeNode<Type>* node):fNode(node){}

	Movement next();
	bool item(Type& item) const;
	Type itemValue() const;
	QString name() const;
	QString currentPath() const;

};

} // End namespace

#include "Tree.tpp"

#endif // TREE_H
