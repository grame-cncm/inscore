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
QString Tree<Type>::currentDir() const
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
bool Tree<Type>::addItem(QString path, const Type &item, bool currentDir)
{
	QString name="";

	if(currentDir){
		TreeNode<Type>* n = extractPath(path, name);
		if(!n)
			return false;
		return n->addItem(name,item)!=-1;
	}

	if( (path = absolutePath(path)).isEmpty() )
		return false;
	name = path.mid(path.lastIndexOf('/')+1);
	path = path.left(path.lastIndexOf('/'));

	return fRoot.createPath(path)->addItem(name,item)!=-1;
}

template <typename Type>
bool Tree<Type>::addDir(QString path)
{
	if( (path = absolutePath(path)).isEmpty() )
		return false;
	fRoot.createPath(path);
	return true;
}

template <typename Type>
TreeNode<Type>* Tree<Type>::extractPath(QString path, QString& name)
{
	if(path.isEmpty())
		return 0;
	QString p = "";
	if(path.at(0)=='/')
		p="/";
	QStringList pathList = path.split("/", QString::SkipEmptyParts);
	name = pathList.last();
	pathList.removeLast();
	p += pathList.join("/");
	return searchDir(p);
}

template <typename Type>
QString Tree<Type>::absolutePath(QString path)
{
	if(path.isEmpty())
		return "";
	if(path.at(0)=='/')
		return path;

	QStringList pathList;
	TreeNode<Type>* n = fCurrentNode;
	while(n->parent()){
		pathList.prepend(n->getName());
		n = n->parent();
	}

	int i = pathList.size();
	pathList.append(path.split("/", QString::SkipEmptyParts));
	while(i<pathList.size()){
		if(pathList.at(i)==".")
			pathList.removeAt(i);
		else if(pathList.at(i)==".."){
			if(i<=0)
				return "";
			pathList.removeAt(--i);
		}else
			i++;
	}
	return "/"+pathList.join("/");
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
	for(int i=0; i<fChildren.size();i++)
		if(fChildren.at(i).getName()==name){
			return &fChildren[i];
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
	foreach (TreeNode<Type> p, fChildren)
		r.push_back(p.getName());

	return r;
}

template<typename Type>
int TreeNode<Type>::childID(QString name) const
{
	for(int i=0; i<fChildren.size();i++)
		if(fChildren.at(i).getName()==name){
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
	fChildren.append(TreeNode<Type>(name));
	fChildren.last().fParent = this;
	fChildren.last().fTree = fTree;
	return fChildren.size()-1;
}


template<typename Type>
TreeNode<Type>* TreeNode<Type>::createPath(QString path)
{
	if(path.isEmpty())
		return this;
	if(path.at(0)=='/')
		path.remove(0,1);
	QString childName = "";
	int idSep = path.indexOf('/');
	if(idSep>-1 && idSep < path.size()-1){
		childName = path.left(idSep);
		path = path.mid(idSep+1);
	}else{
		childName = path;
		path = "";
	}

	TreeNode<Type>* r = searchChildren(childName);
	if(!r)
		r = &fChildren[addChildren(childName)];

	if(path.isEmpty())
		return r;

	return r->createPath(path);
}


template<typename Type>
bool TreeNode<Type>::contains(QString name)
{
	for(int i=0; i<fItems.size();i++)
		if(fItems.at(i).first==name)
			return true;
	for(int i=0; i<fChildren.size();i++)
		if(fChildren.at(i).getName()==name)
			return true;
	return false;
}

template<typename Type>
QString TreeNode<Type>::path() const
{
	QString r=getName();
	const TreeNode<Type> *n = this;
	while(n->parent()){
		r = n->parent()->getName()+"/"+r;
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
	if(!fNode || fPos==-1)
		return false;

	if(fReadingItem){
		if(fPos < fNode->itemCount()){
			item = itemValue();
			return true;
		}
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
			return fNode->nameAt(fPos);
	}else{
		if(fPos < fNode->childrenCount())
			return fNode->childAt(fPos).getName();
	}

	return "";
}

template <typename Type>
QString treeConstIterator<Type>::currentPath() const
{
	if(!fNode)
		return "";
	QString r = fNode->path();
	return r;
}


template <typename Type>
Movement treeConstIterator<Type>::next(){
	if(!fNode)
		return TREE_END;
	fPos++;
	if(fReadingItem){
		if(fPos < fNode->itemCount())
			return ITEM;
		else{
			fPos = 0;
			fReadingItem = false;
		}
	}

	if(fPos < fNode->childrenCount()){
		fNode = &(fNode->childAt(fPos));
		fReadingItem = true;
		fPos = -1;
		return BRANCH;
	}

	if(fNode->parent()){
		QString previousName = fNode->getName();
		fNode = fNode->parent();
		fPos = fNode->childID(previousName);
		return LEAVING_BRANCH;
	}

	fNode = 0;
	return TREE_END;
}

} // End namespace
