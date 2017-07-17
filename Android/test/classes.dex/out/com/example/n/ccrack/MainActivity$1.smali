.class Lcom/example/n/ccrack/MainActivity$1;
.super Ljava/lang/Object;
.source "MainActivity.java"

# interfaces
.implements Landroid/view/View$OnClickListener;


# annotations
.annotation system Ldalvik/annotation/EnclosingMethod;
    value = Lcom/example/n/ccrack/MainActivity;->onCreate(Landroid/os/Bundle;)V
.end annotation

.annotation system Ldalvik/annotation/InnerClass;
    accessFlags = 0x0
    name = null
.end annotation


# instance fields
.field final synthetic this$0:Lcom/example/n/ccrack/MainActivity;


# direct methods
.method constructor <init>(Lcom/example/n/ccrack/MainActivity;)V
    .registers 2
    .param p1, "this$0"    # Lcom/example/n/ccrack/MainActivity;

    .prologue
    .line 37
    iput-object p1, p0, Lcom/example/n/ccrack/MainActivity$1;->this$0:Lcom/example/n/ccrack/MainActivity;

    invoke-direct {p0}, Ljava/lang/Object;-><init>()V

    return-void
.end method


# virtual methods
.method public onClick(Landroid/view/View;)V
    .registers 3
    .param p1, "v"    # Landroid/view/View;

    .prologue
    .line 40
    iget-object v0, p0, Lcom/example/n/ccrack/MainActivity$1;->this$0:Lcom/example/n/ccrack/MainActivity;

    # invokes: Lcom/example/n/ccrack/MainActivity;->biubiubiu()V
    invoke-static {v0}, Lcom/example/n/ccrack/MainActivity;->access$000(Lcom/example/n/ccrack/MainActivity;)V

    .line 42
    return-void
.end method
