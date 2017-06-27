.class public Lcom/example/n/ccrack/okActivity;
.super Landroid/support/v7/app/AppCompatActivity;
.source "okActivity.java"


# direct methods
.method public constructor <init>()V
    .registers 1

    .prologue
    .line 7
    invoke-direct {p0}, Landroid/support/v7/app/AppCompatActivity;-><init>()V

    return-void
.end method


# virtual methods
.method protected onCreate(Landroid/os/Bundle;)V
    .registers 4
    .param p1, "savedInstanceState"    # Landroid/os/Bundle;

    .prologue
    .line 11
    invoke-super {p0, p1}, Landroid/support/v7/app/AppCompatActivity;->onCreate(Landroid/os/Bundle;)V

    .line 12
    const v1, 0x7f04001c

    invoke-virtual {p0, v1}, Lcom/example/n/ccrack/okActivity;->setContentView(I)V

    .line 13
    const-string v0, "21312312312ssadasdasdas"

    .line 14
    .local v0, "a":Ljava/lang/String;
    const-string v1, "ggggg"

    invoke-static {v1, v0}, Landroid/util/Log;->d(Ljava/lang/String;Ljava/lang/String;)I

    .line 17
    return-void
.end method
