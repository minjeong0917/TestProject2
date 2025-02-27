// Fill out your copyright notice in the Description page of Project Settings.

#include "Title/UI/TitleWidget.h"
#include "TestProject2.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "Blueprint/WidgetLayoutLibrary.h"



void UTitleWidget::OrderComplete()
{
    if (!OrderImage) return;

    GetWorld()->GetTimerManager().SetTimer(OpacityTimerHandle, this, &UTitleWidget::UpdateWidgetOpacity, 0.01f, true);
}


void UTitleWidget::NewOrder()
{
    if (!OrderImage) return;

    MoveTimeElapsed = 0.0f;
    CurPosition = OrderImage->GetRenderTransform().Translation;
    CurScale = OrderImage->GetRenderTransform().Scale;

    FVector2D ScreenSize = UWidgetLayoutLibrary::GetViewportSize(this);
    float WidgetHeight = OrderImage->GetDesiredSize().Y;
    float FinalPosition = ScreenSize.X * 1.5f;

    OrderImage->SetRenderTransformAngle(-20.0f);
    OrderImage->SetRenderScale({ CurScale.X,CurScale.Y * 2 });
    OrderImage->SetRenderTranslation({ FinalPosition, -WidgetHeight * 2.5f });
    OrderImage->SetColorAndOpacity({ OrderImage->GetColorAndOpacity().R, OrderImage->GetColorAndOpacity().G, OrderImage->GetColorAndOpacity().B, 1.0f });

    GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle, this, &UTitleWidget::UpdateWidgetPosition, 0.01f, true);
}


void UTitleWidget::UpdateWidgetPosition()
{
    if (!OrderImage) return;

    FVector2D CurrentPosition = OrderImage->GetRenderTransform().Translation;
    float CurrentAngle = OrderImage->GetRenderTransform().Angle;

    if (CurrentPosition.X <= CurPosition.X && CurrentAngle >= 0.0f)
    {
        OrderImage->SetRenderScale(CurScale);
        OrderImage->SetRenderTranslation(CurPosition);
        GetWorld()->GetTimerManager().ClearTimer(MoveTimerHandle);
        return;
    }
    else
    {
        if (CurrentPosition.X > CurPosition.X)
        {
            OrderImage->SetRenderTranslation(CurrentPosition - FVector2D(TargetOffset.X + MoveTimeElapsed, 0));
        }
        if (CurrentAngle < 0.0f)
        {
            OrderImage->SetRenderTransformAngle(CurrentAngle + 0.5f);
        }
    }

    MoveTimeElapsed += 0.1f;
}



void UTitleWidget::UpdateWidgetOpacity()
{
    if (!OrderImage) return;

    if (OrderImage->GetColorAndOpacity().A <= 0.0f)
    {
        GetWorld()->GetTimerManager().ClearTimer(OpacityTimerHandle);
        return;
    }

    float CurOpacity = OrderImage->GetColorAndOpacity().A;
    OrderImage->SetColorAndOpacity({ OrderImage->GetColorAndOpacity().R, OrderImage->GetColorAndOpacity().G, OrderImage->GetColorAndOpacity().B, FMath::Clamp(CurOpacity - OpacityOffset, 0.0f, 1.0f) });

}