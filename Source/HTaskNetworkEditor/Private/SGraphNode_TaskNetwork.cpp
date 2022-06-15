#include "SGraphNode_TaskNetwork.h"
#include "AIGraphNode.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"
#include "STaskNetworkPin.h"

void SGraphNode_TaskNetwork::Construct(const FArguments& InArgs, UAIGraphNode* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
}

void SGraphNode_TaskNetwork::UpdateGraphNode()
{
	TSharedPtr<SNodeTitle> NodeTitle = SNew(SNodeTitle, GraphNode);
	const auto AINode = Cast<UAIGraphNode>(GraphNode);

	auto GetDescription = [AINode]()
	{
		if (IsValid(AINode))
		{
			return AINode->GetDescription(); 
		}
		return FText();
	};
	
	// this->ContentScale.Bind(this, &SGraphNode::GetContentScale);
	this->GetOrAddSlot(ENodeZone::Center)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		[
			SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.Body"))
			.Padding(0.0f)
			.BorderBackgroundColor(FSlateColor(FColor::Cyan))
			[
				SNew(SOverlay)

				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SHorizontalBox) // Node is laid out Horizontally
					+ SHorizontalBox::Slot() //Input Pin Area
					.AutoWidth()
					[
						SNew(SBox)
						.MinDesiredWidth(8.0f)
						[
							SAssignNew(LeftNodeBox, SVerticalBox)
						]
					]

					+ SHorizontalBox::Slot() // Node Body, laid out Vertically
					.Padding(2.0f)
					[
						SNew(SVerticalBox)
						+SVerticalBox::Slot()
						.FillHeight(20.0f)
						[
							SNew(SInlineEditableTextBlock)
							.Style(FEditorStyle::Get(), "Graph.StateNode.NodeTitleInlineEditableText")
							.Text(NodeTitle.Get(), &SNodeTitle::GetHeadTitle)
							.IsReadOnly(true)
						]
						+SVerticalBox::Slot()
						.AutoHeight()
						[
							NodeTitle.ToSharedRef()
						]
						+SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(SBorder)
							.BorderBackgroundColor(FSlateColor(FColor::White))
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							[
								SAssignNew(InlineEditableText, SInlineEditableTextBlock)
								.Style(FEditorStyle::Get(), "Graph.StateNode.NodeTitleInlineEditableText")
								.Text(TAttribute<FText>::CreateLambda(GetDescription))
								.IsReadOnly(true)
								.IsSelected(false)
							]
						]
					]

					+ SHorizontalBox::Slot() // Output Pin Area
					.AutoWidth()
					[
						SNew(SBox)
						.MinDesiredWidth(8.0f)
						[
							SAssignNew(RightNodeBox, SVerticalBox)
						]
					]
				]
			]
		];

	CreatePinWidgets();
}

void SGraphNode_TaskNetwork::CreatePinWidgets()
{
	for (auto* Pin : GraphNode->Pins)
	{
		if (!Pin->bHidden)
		{
			TSharedPtr<SGraphPin> PinWidget = SNew(STaskNetworkPin, Pin);
			AddPin(PinWidget.ToSharedRef());
		}
	}
}
