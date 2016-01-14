namespace qarchive{

template <typename Type>
Tree<Type>::Tree(): fRoot(""), fCurrentNode(&fRoot)
{
	fRoot.fTree = this;
}

template <typename Type>
TreeNode<Type> *Tree<Type>::changeDir(QString path, bool& dirFound)
{
	TreeNode<Type>* n = searchDir(path);
	dirFound = n;
	if(n)
		fCurrentNode = n;
	return fCurrentNode;
}

template <typename Type>
TreeNode<Type>* Tree<Type>::upDir()
{
	if(!fCurrentNode->parent())
		return 0;
	fCurrentNode = fCurrentNode->parent();
	return fCurrentNode;
}

template <typename Type>
TreeNode<Type> *Tree<Type>::searchDir(QString path)
{
	if(!path.size())
		return fCurrentNode;

	TreeNode<Type>* n = fCurrentNode;

	if(path.at(0) == '/')
		n = &fRoot;

	QStringList p = path.split("/", QString::SkipEmptyParts);

	while(!p.isEmpty()){
		QString d = p.first();
		p.removeFirst();

		if(d == ".")
			continue;
		if(d == ".."){
			if(n->parent()){
				n = n->parent();
				continue;
			}else
				return 0;
		}

		TreeNode<Type>* t;
		if( (t = n->searchChildren(d)) ){
			n = t;
			continue;
		}else
			return 0;
	}
	return n;
}

template <typename Type>
QString Tree<Type>::currentDir()
{
	return fCurrentNode->path();
}

template <typename Type>
bool Tree<Type>::setCurrentNode(TreeNode<Type>* node)
{
	if(node->fTree!=this)
		return false;
	fCurrentNode = node;
	return true;
}

template <typename Type>
bool Tree<Type>::searchItem(QString path, Type &item)
{
	QString name="";
	TreeNode<Type>* n = extractPath(path, name);
	if(!n)
		return false;

	return n->searchItem(name, item);
}

template <typename Type>
bool Tree<Type>::addItem(QString path, const Type &item)
{
	QString name="";
	TreeNode<Type>* n = extractPath(path, name);
	if(!n)
		return false;
	return n->addItem(name,item)!=-1;
}

template <typename Type>
bool Tree<Type>::addDir(QString path)
{
	QString name="";
	TreeNode<Type>* n = extractPath(path, name);
	if(!n)
		return false;
	return n->addChildren(name)!=-1;
}

template <typename Type>
TreeNode<Type>* Tree<Type>::extractPath(QString path, QString& name)
{
	QString p = "";
	if(path.at(0)=='/')
		p="/";
	QStringList pathList = path.split("/", QString::SkipEmptyParts);
	name = pathList.last();
	pathList.removeLast();
	p += pathList.join("/");
	return searchDir(p);
}


/*************************************************
 *                    TreeNode                   *
 * **********************************************/

template<typename Type>
bool TreeNode<Type>::searchItem(QString name, Type &item) const
{
	for(int i=0; i<fItems.size();i++)
		if(fItems.at(i).first==name){
			item = fItems.at(i).second;
			return true;
		}

	return false;
}

template<typename Type>
TreeNode<Type>* TreeNode<Type>::searchChildren(QString name)
{
	for(int i=0; i<fChildrenNodes.size();i++)
		if(fChildrenNodes.at(i).getName()==name){
			return &fChildrenNodes[i];
		}

	return 0;
}

template<typename Type>
QStringList TreeNode<Type>::itemsNames() const
{
	QStringList r;
	QListIterator<QPair<QString,Type>> it(fItems);
	while(it.hasNext())
		r.push_back(it.next().first);

	return r;
}

template<typename Type>
QStringList TreeNode<Type>::childrenNames() const
{
	QStringList r;
	foreach (TreeNode<Type> p, fChildrenNodes)
		r.push_back(p.getName());

	return r;
}

template<typename Type>
int TreeNode<Type>::childID(QString name) const
{
	for(int i=0; i<fChildrenNodes.size();i++)
		if(fChildrenNodes.at(i).getName()==name){
			return i;
		}

	return -1;
}

template<typename Type>
int TreeNode<Type>::addItem(QString name, const Type &item)
{
	if(contains(name))
		return -1;
	QPair<QString, Type> p(name,item);
	fItems.append(p);
	return fItems.size()-1;
}

template<typename Type>
int TreeNode<Type>::addChildren(QString name)
{
	if(contains(name))
		return -1;
	fChildrenNodes.append(TreeNode<Type>(name));
	fChildrenNodes.last().fParent = this;
	fChildrenNodes.last().fTree = fTree;
	return fChildrenNodes.size()-1;
}


template<typename Type>
bool TreeNode<Type>::contains(QString name)
{
	for(int i=0; i<fItems.size();i++)
		if(fItems.at(i).first==name)
			return true;
	for(int i=0; i<fChildrenNodes.size();i++)
		if(fChildrenNodes.at(i).getName()==name)
			return true;
	return false;
}

template<typename Type>
QString TreeNode<Type>::path() const
{
	QString r="/"+getName();
	const TreeNode<Type> *n = this;
	while(n->parent()){
		r = "/"+n->parent()->getName()+r;
		n = n->parent();
	}
	return r;
}


/****************************************************
 *                treeConstIterator                 *
 * *************************************************/

template <typename Type>
bool treeConstIterator<Type>::item(Type &item) const
{
	if(!fNode)
		return false;

	if(fReadingItem){
		if(fPos < fNode->itemCount())
			item = itemValue();
	}

	return false;
}

template <typename Type>
Type treeConstIterator<Type>::itemValue() const
{
	return fNode->at(fPos);
}

template <typename Type>
QString treeConstIterator<Type>::name() const
{
	if(!fNode)
		return "";

	if(fPos==-1)
		return fNode->getName();

	if(fReadingItem){
		if(fPos < fNode->itemCount())
			return fNode->items().at(fPos).first;
	}else{
		if(fPos < fNode->nodeCount())
			return fNode->nodeAt(fPos).getName();
	}

	return "";
}

template <typename Type>
QString treeConstIterator<Type>::currentPath() const
{
	if(!fNode)
		return false;
	return fNode->path();
}


template <typename Type>
Movement treeConstIterator<Type>::next(){
	if(!fNode)
		return TreeEnd;
	fPos++;
	if(fReadingItem){
		if(fPos < fNode->itemCount())
			return Item;
		else{
			fPos = 0;
			fReadingItem = false;
		}
	}

	if(fPos < fNode->nodeCount()){
		fNode = &(fNode->childrenList()[fPos]);
		fReadingItem = true;
		fPos = -1;
		return Branch;
	}

	if(fNode->parent()){
		QString previousName = fNode->getName();
		fNode = fNode->parent();
		fPos = fNode->childID(previousName);
		return LeavingBranch;
	}

	fNode = 0;
	return TreeEnd;
}

} // End namespace
