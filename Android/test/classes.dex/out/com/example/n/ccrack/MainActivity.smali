.class public Lcom/example/n/ccrack/MainActivity;
.super Landroid/support/v7/app/AppCompatActivity;
.source "MainActivity.java"


# instance fields
.field private bn_login:Landroid/widget/Button;

.field private et_pass:Landroid/widget/EditText;

.field private et_phone:Landroid/widget/EditText;


# direct methods
.method static constructor <clinit>()V
    .registers 1

    .prologue
    .line 23
    const-string v0, "native-lib"

    invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V

    .line 24
    return-void
.end method

.method public constructor <init>()V
    .registers 1

    .prologue
    .line 17
    invoke-direct {p0}, Landroid/support/v7/app/AppCompatActivity;-><init>()V

    return-void
.end method

.method static synthetic access$000(Lcom/example/n/ccrack/MainActivity;)V
    .registers 1
    .param p0, "x0"    # Lcom/example/n/ccrack/MainActivity;

    .prologue
    .line 17
    invoke-direct {p0}, Lcom/example/n/ccrack/MainActivity;->biubiubiu()V

    return-void
.end method

.method private biubiubiu()V
    .registers 7

    .prologue
    .line 99
    iget-object v4, p0, Lcom/example/n/ccrack/MainActivity;->et_pass:Landroid/widget/EditText;

    invoke-virtual {v4}, Landroid/widget/EditText;->getText()Landroid/text/Editable;

    move-result-object v4

    invoke-virtual {v4}, Ljava/lang/Object;->toString()Ljava/lang/String;

    move-result-object v1

    .line 100
    .local v1, "pass":Ljava/lang/String;
    iget-object v4, p0, Lcom/example/n/ccrack/MainActivity;->et_phone:Landroid/widget/EditText;

    invoke-virtual {v4}, Landroid/widget/EditText;->getText()Landroid/text/Editable;

    move-result-object v4

    invoke-virtual {v4}, Ljava/lang/Object;->toString()Ljava/lang/String;

    move-result-object v2

    .line 101
    .local v2, "phone":Ljava/lang/String;
    invoke-direct {p0, v2}, Lcom/example/n/ccrack/MainActivity;->checkphone(Ljava/lang/String;)Z

    move-result v3

    .line 109
    .local v3, "ret":Z
    invoke-direct {p0, v1}, Lcom/example/n/ccrack/MainActivity;->encpass(Ljava/lang/String;)Ljava/lang/String;

    move-result-object v0

    .line 110
    .local v0, "encpass":Ljava/lang/String;
    const-string v4, "crackme"

    invoke-static {v4, v0}, Landroid/util/Log;->d(Ljava/lang/String;Ljava/lang/String;)I

    .line 111
    invoke-virtual {p0, v0, v2}, Lcom/example/n/ccrack/MainActivity;->checkit(Ljava/lang/String;Ljava/lang/String;)Z

    move-result v4

    if-eqz v4, :cond_32

    .line 112
    new-instance v4, Landroid/content/Intent;

    const-class v5, Lcom/example/n/ccrack/okActivity;

    invoke-direct {v4, p0, v5}, Landroid/content/Intent;-><init>(Landroid/content/Context;Ljava/lang/Class;)V

    invoke-virtual {p0, v4}, Lcom/example/n/ccrack/MainActivity;->startActivity(Landroid/content/Intent;)V

    .line 117
    :goto_31
    return-void

    .line 114
    :cond_32
    const-string v4, "\u767b\u5f55\u5931\u8d25"

    const/4 v5, 0x0

    invoke-static {p0, v4, v5}, Landroid/widget/Toast;->makeText(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;

    move-result-object v4

    invoke-virtual {v4}, Landroid/widget/Toast;->show()V

    .line 115
    const-string v4, "ggggggg"

    const/4 v5, 0x1

    invoke-static {p0, v4, v5}, Landroid/widget/Toast;->makeText(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;

    move-result-object v4

    invoke-virtual {v4}, Landroid/widget/Toast;->show()V

    goto :goto_31
.end method

.method private static byteArrayToHex([B)Ljava/lang/String;
    .registers 9
    .param p0, "byteArray"    # [B

    .prologue
    .line 72
    const/16 v5, 0x10

    new-array v1, v5, [C

    fill-array-data v1, :array_30

    .line 73
    .local v1, "hexDigits":[C
    array-length v5, p0

    mul-int/lit8 v5, v5, 0x2

    new-array v4, v5, [C

    .line 74
    .local v4, "resultCharArray":[C
    const/4 v2, 0x0

    .line 75
    .local v2, "index":I
    array-length v6, p0

    const/4 v5, 0x0

    move v3, v2

    .end local v2    # "index":I
    .local v3, "index":I
    :goto_10
    if-ge v5, v6, :cond_29

    aget-byte v0, p0, v5

    .line 76
    .local v0, "b":B
    add-int/lit8 v2, v3, 0x1

    .end local v3    # "index":I
    .restart local v2    # "index":I
    ushr-int/lit8 v7, v0, 0x4

    and-int/lit8 v7, v7, 0xf

    aget-char v7, v1, v7

    aput-char v7, v4, v3

    .line 77
    add-int/lit8 v3, v2, 0x1

    .end local v2    # "index":I
    .restart local v3    # "index":I
    and-int/lit8 v7, v0, 0xf

    aget-char v7, v1, v7

    aput-char v7, v4, v2

    .line 75
    add-int/lit8 v5, v5, 0x1

    goto :goto_10

    .line 79
    .end local v0    # "b":B
    :cond_29
    new-instance v5, Ljava/lang/String;

    invoke-direct {v5, v4}, Ljava/lang/String;-><init>([C)V

    return-object v5

    .line 72
    nop

    :array_30
    .array-data 2
        0x30s
        0x31s
        0x32s
        0x33s
        0x34s
        0x35s
        0x36s
        0x37s
        0x38s
        0x39s
        0x61s
        0x62s
        0x63s
        0x64s
        0x65s
        0x66s
    .end array-data
.end method

.method private checkpass(Ljava/lang/String;)Z
    .registers 4
    .param p1, "pass"    # Ljava/lang/String;

    .prologue
    .line 64
    if-eqz p1, :cond_9

    invoke-virtual {p1}, Ljava/lang/String;->length()I

    move-result v0

    const/4 v1, 0x6

    if-eq v0, v1, :cond_b

    .line 65
    :cond_9
    const/4 v0, 0x0

    .line 67
    :goto_a
    return v0

    :cond_b
    const/4 v0, 0x1

    goto :goto_a
.end method

.method private checkphone(Ljava/lang/String;)Z
    .registers 5
    .param p1, "phone"    # Ljava/lang/String;

    .prologue
    const/4 v0, 0x0

    .line 55
    if-eqz p1, :cond_b

    invoke-virtual {p1}, Ljava/lang/String;->length()I

    move-result v1

    const/16 v2, 0xb

    if-eq v1, v2, :cond_c

    .line 59
    :cond_b
    :goto_b
    return v0

    .line 57
    :cond_c
    const-string v1, "139"

    invoke-virtual {p1, v1}, Ljava/lang/String;->startsWith(Ljava/lang/String;)Z

    move-result v1

    if-eqz v1, :cond_b

    .line 58
    const/4 v0, 0x1

    goto :goto_b
.end method

.method private encpass(Ljava/lang/String;)Ljava/lang/String;
    .registers 6
    .param p1, "pass"    # Ljava/lang/String;

    .prologue
    .line 83
    const/4 v2, 0x0

    .line 85
    .local v2, "resultByteArray":[B
    :try_start_1
    const-string v3, "MD5"

    invoke-static {v3}, Ljava/security/MessageDigest;->getInstance(Ljava/lang/String;)Ljava/security/MessageDigest;

    move-result-object v1

    .line 86
    .local v1, "md":Ljava/security/MessageDigest;
    invoke-virtual {p1}, Ljava/lang/String;->getBytes()[B

    move-result-object v3

    invoke-virtual {v1, v3}, Ljava/security/MessageDigest;->update([B)V

    .line 87
    invoke-virtual {v1}, Ljava/security/MessageDigest;->digest()[B
    :try_end_11
    .catch Ljava/lang/Exception; {:try_start_1 .. :try_end_11} :catch_17

    move-result-object v2

    .line 94
    .end local v1    # "md":Ljava/security/MessageDigest;
    :goto_12
    invoke-static {v2}, Lcom/example/n/ccrack/MainActivity;->byteArrayToHex([B)Ljava/lang/String;

    move-result-object v3

    return-object v3

    .line 89
    :catch_17
    move-exception v0

    .line 91
    .local v0, "e":Ljava/lang/Exception;
    invoke-virtual {v0}, Ljava/lang/Exception;->printStackTrace()V

    goto :goto_12
.end method


# virtual methods
.method public native checkit(Ljava/lang/String;Ljava/lang/String;)Z
.end method

.method protected onCreate(Landroid/os/Bundle;)V
    .registers 4
    .param p1, "savedInstanceState"    # Landroid/os/Bundle;

    .prologue
    .line 31
    invoke-super {p0, p1}, Landroid/support/v7/app/AppCompatActivity;->onCreate(Landroid/os/Bundle;)V

    .line 32
    const v0, 0x7f04001b

    invoke-virtual {p0, v0}, Lcom/example/n/ccrack/MainActivity;->setContentView(I)V

    .line 34
    const v0, 0x7f0b005f

    invoke-virtual {p0, v0}, Lcom/example/n/ccrack/MainActivity;->findViewById(I)Landroid/view/View;

    move-result-object v0

    check-cast v0, Landroid/widget/EditText;

    iput-object v0, p0, Lcom/example/n/ccrack/MainActivity;->et_pass:Landroid/widget/EditText;

    .line 35
    const v0, 0x7f0b005e

    invoke-virtual {p0, v0}, Lcom/example/n/ccrack/MainActivity;->findViewById(I)Landroid/view/View;

    move-result-object v0

    check-cast v0, Landroid/widget/EditText;

    iput-object v0, p0, Lcom/example/n/ccrack/MainActivity;->et_phone:Landroid/widget/EditText;

    .line 36
    const v0, 0x7f0b0060

    invoke-virtual {p0, v0}, Lcom/example/n/ccrack/MainActivity;->findViewById(I)Landroid/view/View;

    move-result-object v0

    check-cast v0, Landroid/widget/Button;

    iput-object v0, p0, Lcom/example/n/ccrack/MainActivity;->bn_login:Landroid/widget/Button;

    .line 37
    iget-object v0, p0, Lcom/example/n/ccrack/MainActivity;->bn_login:Landroid/widget/Button;

    new-instance v1, Lcom/example/n/ccrack/MainActivity$1;

    invoke-direct {v1, p0}, Lcom/example/n/ccrack/MainActivity$1;-><init>(Lcom/example/n/ccrack/MainActivity;)V

    invoke-virtual {v0, v1}, Landroid/widget/Button;->setOnClickListener(Landroid/view/View$OnClickListener;)V

    .line 45
    return-void
.end method
