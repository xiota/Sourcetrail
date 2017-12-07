#include "data/NodeTypeSet.h"

#include "utility/utility.h"
#include "utility/utilityMath.h"

NodeTypeSet NodeTypeSet::all()
{
	NodeTypeSet ret;
	ret.m_nodeTypeMask = ~0;
	return ret;
}

NodeTypeSet NodeTypeSet::none()
{
	return NodeTypeSet();
}

NodeTypeSet::NodeTypeSet()
{
	m_nodeTypeMask = 0;
}

NodeTypeSet::NodeTypeSet(const NodeType& type)
{
	m_nodeTypeMask = nodeTypeToMask(type);
}

bool NodeTypeSet::operator==(const NodeTypeSet& other) const
{
	return m_nodeTypeMask == other.m_nodeTypeMask;
}

bool NodeTypeSet::operator!=(const NodeTypeSet& other) const
{
	return !operator==(other);
}

void NodeTypeSet::invert()
{
	m_nodeTypeMask = ~m_nodeTypeMask;
}

NodeTypeSet NodeTypeSet::getInverse() const
{
	NodeTypeSet ret(*this);
	ret.invert();
	return ret;
}

void NodeTypeSet::add(const NodeTypeSet& typeSet)
{
	m_nodeTypeMask |= typeSet.m_nodeTypeMask;
}

std::vector<NodeType> NodeTypeSet::getNodeTypes() const
{
	std::vector<NodeType> nodeTypes;

	for (const NodeType& type : s_allNodeTypes)
	{
		if (m_nodeTypeMask & nodeTypeToMask(type))
		{
			nodeTypes.push_back(type);
		}
	}

	return nodeTypes;
}

void NodeTypeSet::remove(const NodeTypeSet& typeSet)
{
	m_nodeTypeMask &= ~typeSet.m_nodeTypeMask;
}

NodeTypeSet NodeTypeSet::getWithRemoved(const NodeTypeSet& typeSet) const
{
	NodeTypeSet ret(*this);
	ret.remove(typeSet);
	return ret;
}

void NodeTypeSet::removeIf(const std::function<bool(const NodeType&)> condition)
{
	for (const NodeType& type : s_allNodeTypes)
	{
		if (m_nodeTypeMask & nodeTypeToMask(type) && condition(type))
		{
			remove(type);
		}
	}
}

NodeTypeSet NodeTypeSet::getWithRemovedIf(const std::function<bool(const NodeType&)> condition) const
{
	NodeTypeSet ret(*this);
	ret.removeIf(condition);
	return ret;
}

bool NodeTypeSet::isEmpty() const
{
	return m_nodeTypeMask == 0;
}

bool NodeTypeSet::contains(const NodeType& type) const
{
	return m_nodeTypeMask & nodeTypeToMask(type);
}

bool NodeTypeSet::intersectsWith(const NodeTypeSet& typeSet) const
{
	return m_nodeTypeMask & typeSet.m_nodeTypeMask;
}

std::vector<Id> NodeTypeSet::getNodeTypeIds() const
{
	std::vector<Id> ids;

	for (const NodeType& type: s_allNodeTypes)
	{
		if (m_nodeTypeMask & nodeTypeToMask(type))
		{
			ids.push_back(type.getId());
		}
	}

	return ids;
}

NodeTypeSet::MaskType NodeTypeSet::nodeTypeToMask(const NodeType& nodeType)
{
	// todo: convert to mask if ids are not power of two anymore
	return nodeType.getId();
}

const std::vector<NodeType> NodeTypeSet::s_allNodeTypes = {
	NodeType(NodeType::NODE_SYMBOL),
	NodeType(NodeType::NODE_TYPE),
	NodeType(NodeType::NODE_BUILTIN_TYPE),
	NodeType(NodeType::NODE_NAMESPACE),
	NodeType(NodeType::NODE_PACKAGE),
	NodeType(NodeType::NODE_STRUCT),
	NodeType(NodeType::NODE_CLASS),
	NodeType(NodeType::NODE_INTERFACE),
	NodeType(NodeType::NODE_FIELD),
	NodeType(NodeType::NODE_FUNCTION),
	NodeType(NodeType::NODE_METHOD),
	NodeType(NodeType::NODE_ENUM),
	NodeType(NodeType::NODE_ENUM_CONSTANT),
	NodeType(NodeType::NODE_TYPEDEF),
	NodeType(NodeType::NODE_TEMPLATE_PARAMETER_TYPE),
	NodeType(NodeType::NODE_TYPE_PARAMETER),
	NodeType(NodeType::NODE_FILE),
	NodeType(NodeType::NODE_MACRO),
	NodeType(NodeType::NODE_UNION)
};