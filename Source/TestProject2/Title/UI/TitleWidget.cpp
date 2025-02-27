// Fill out your copyright notice in the Description page of Project Settings.

#include "Title/UI/TitleWidget.h"
#include "TestProject2.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "Blueprint/WidgetLayoutLibrary.h"



void UTitleWidget::OrderComplete()
{
    if (!Orders[CompleteOrderNum].BackgroundImage) return;

    GetWorld()->GetTimerManager().SetTimer(OpacityTimerHandle, this, &UTitleWidget::UpdateImageOpacity, 0.01f, true);

}


void UTitleWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    Orders.SetNum(3);

    Orders[0].BackgroundImage = OrderBackground_0;
    Orders[1].BackgroundImage = OrderBackground_1;
    Orders[2].BackgroundImage = OrderBackground_2;

    float StartPosX = 20.0f;
    float offset = 10.0f;
    for (int i = 0; i < Orders.Num(); i++)
    {

        Orders[i].Position = { StartPosX + offset * i, 0.0f };
        //Orders[i].BackgroundImage->SetRenderTranslation(Orders[i].Position);
    }

}


void UTitleWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    UpdateImagePosition(InDeltaTime);
}

void UTitleWidget::UpdateImageOpacity()
{

    if (Orders[CompleteOrderNum].BackgroundImage->GetColorAndOpacity().A <= 0.0f)
    {
        Orders[CompleteOrderNum].BackgroundImage->SetVisibility(ESlateVisibility::Collapsed);

        for (int i = CompleteOrderNum; i < Orders.Num() - 1; i++)
        {
            //const TArray<UPanelSlot> slots = CanvasPanel->GetSlots();
            //UCanvasPanelSlot CPSlot = Cast<UCanvasPanelSlot>(slots[0]);
            //CPSlot->SetPosition(CPSlot->GetPosition() + FVector2D(100, 0));

            float value = Orders[i].Position.X - 260;
            //Orders[i + 1].BackgroundImage->SetRenderTranslation({ -260.f, 0.0f });
            //Orders[i + 1].BackgroundImage->SetRenderTranslation({ Orders[i].Position.X - 260 /Orders[i].BackgroundImage->GetDesiredSize().X/ , 0.0f });
        }

        for (int i = CompleteOrderNum; i < Size - 1; i++)
        {
            Orders[i] = Orders[i + 1];
            const FWidgetTransform& trfm = Orders[i].BackgroundImage->GetRenderTransform();
            Orders[i].BackgroundImage->SetRenderTranslation({ trfm.Translation.X - 280.f, 0.0f });
            //Orders[i].BackgroundImage = Orders[i + 1].BackgroundImage;
        }

        Size--;


        GetWorld()->GetTimerManager().ClearTimer(OpacityTimerHandle);
        return;
    }

    float CurOpacity = Orders[CompleteOrderNum].BackgroundImage->GetColorAndOpacity().A;
    Orders[CompleteOrderNum].BackgroundImage->SetColorAndOpacity({ Orders[CompleteOrderNum].BackgroundImage->GetColorAndOpacity().R, Orders[CompleteOrderNum].BackgroundImage->GetColorAndOpacity().G, Orders[CompleteOrderNum].BackgroundImage->GetColorAndOpacity().B, FMath::Clamp(CurOpacity - OpacityOffset, 0.0f, 1.0f) });



}

void UTitleWidget::UpdateImagePosition(float InDeltaTime)
{


}