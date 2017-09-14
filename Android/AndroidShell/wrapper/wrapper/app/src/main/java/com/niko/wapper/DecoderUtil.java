package com.niko.wapper;


public class DecoderUtil {
    private static final String CHARSET = "utf-8";

    private static byte[] a = new byte[]{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1,
            -1, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5, 6,
            7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1,
            26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
            51, -1, -1, -1, -1, -1};

    private static char[] b = new char[]{
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S'
            , 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'
            , 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4'
            , '5', '6', '7', '8', '9', '+', '/', '='};

    private static byte[] dec(String arg14) {
        int v9_1;
        char v8_1;
        int v8;
        byte[] v0 = null;
        if (arg14 != null) {
            char[] v6 = arg14.toCharArray();
            int v1 = DecoderUtil.a(v6);
            if (v1 % 4 == 0) {
                int v7 = v1 / 4;
                if (v7 == 0) {
                    v0 = new byte[0];
                } else {
                    byte[] v1_1 = new byte[v7 * 3];
                    int v2 = 0;
                    int v4 = 0;
                    int v5 = 0;
                    while (true) {
                        if (v5 < v7 - 1) {
                            v8 = v2 + 1;
                            char v9 = v6[v2];
                            if (DecoderUtil.c(v9)) {
                                v2 = v8 + 1;
                                v8_1 = v6[v8];
                                if (DecoderUtil.c(v8_1)) {
                                    int v10 = v2 + 1;
                                    char v11 = v6[v2];
                                    if (DecoderUtil.c(v11)) {
                                        v2 = v10 + 1;
                                        char v10_1 = v6[v10];
                                        if (DecoderUtil.c(v10_1)) {
                                            v9_1 = DecoderUtil.a[v9];
                                            v8 = DecoderUtil.a[v8_1];
                                            int v11_1 = DecoderUtil.a[v11];
                                            v10 = DecoderUtil.a[v10_1];
                                            int v12 = v4 + 1;
                                            v1_1[v4] = ((byte) (v9_1 << 2 | v8 >> 4));
                                            v9_1 = v12 + 1;
                                            v1_1[v12] = ((byte) ((v8 & 15) << 4 | v11_1 >> 2 & 15));
                                            v4 = v9_1 + 1;
                                            v1_1[v9_1] = ((byte) (v11_1 << 6 | v10));
                                            ++v5;
                                            continue;
                                        }
                                    }
                                }
                            }
                        } else {
                            break;
                        }

                        return v0;
                    }

                    v7 = v2 + 1;
                    char v2_1 = v6[v2];
                    if (DecoderUtil.c(v2_1)) {
                        v8 = v7 + 1;
                        char v7_1 = v6[v7];
                        if (DecoderUtil.c(v7_1)) {
                            v2 = DecoderUtil.a[v2_1];
                            v7 = DecoderUtil.a[v7_1];
                            v9_1 = v8 + 1;
                            v8_1 = v6[v8];
                            char v6_1 = v6[v9_1];
                            if ((DecoderUtil.c(v8_1)) && (DecoderUtil.c(v6_1))) {
                                int v0_1 = DecoderUtil.a[v8_1];
                                int v3 = DecoderUtil.a[v6_1];
                                v5 = v4 + 1;
                                v1_1[v4] = ((byte) (v2 << 2 | v7 >> 4));
                                v1_1[v5] = ((byte) ((v7 & 15) << 4 | v0_1 >> 2 & 15));
                                v1_1[v5 + 1] = ((byte) (v0_1 << 6 | v3));
                                return v1_1;
                            }

                            if ((DecoderUtil.b(v8_1)) && (DecoderUtil.b(v6_1))) {
                                if ((v7 & 15) == 0) {
                                    v0 = new byte[v5 * 3 + 1];
                                    System.arraycopy(v1_1, 0, v0, 0, v5 * 3);
                                    v0[v4] = ((byte) (v2 << 2 | v7 >> 4));
                                } else {
                                }

                                return v0;
                            }

                            if (DecoderUtil.b(v8_1)) {
                                return v0;
                            }

                            if (!DecoderUtil.b(v6_1)) {
                                return v0;
                            }

                            int v6_2 = DecoderUtil.a[v8_1];
                            if ((v6_2 & 3) != 0) {
                                return v0;
                            }

                            v0 = new byte[v5 * 3 + 2];
                            System.arraycopy(v1_1, 0, v0, 0, v5 * 3);
                            v0[v4] = ((byte) (v2 << 2 | v7 >> 4));
                            v0[v4 + 1] = ((byte) ((v7 & 15) << 4 | v6_2 >> 2 & 15));
                        }
                    }
                }
            }
        }

        return v0;
    }


    private static int a(char[] arg5) {
        int v0;
        int v1 = 0;
        if (arg5 != null) {
            int v3 = arg5.length;
            int v2 = 0;
            while (v2 < v3) {
                if (!DecoderUtil.a(arg5[v2])) {
                    v0 = v1 + 1;
                    arg5[v1] = arg5[v2];
                } else {
                    v0 = v1;
                }

                ++v2;
                v1 = v0;
            }
        }

        return v1;
    }

    private static boolean a(char arg1) {
        boolean v0 = arg1 == 32 || arg1 == 13 || arg1 == 10 || arg1 == 9 ? true : false;
        return v0;
    }

    private static boolean b(char arg1) {
        boolean v0 = arg1 == 61 ? true : false;
        return v0;
    }

    private static boolean c(char arg2) {
        boolean v0 = arg2 >= 128 || DecoderUtil.a[arg2] == -1 ? false : true;
        return v0;
    }

    ///////////////////////////////////////////////////////////
    ////
    /// Simple decode
    /// base64 decode
    /////////////////////////////////////////////////////////////
    public static String b642String(String data) {
        if (data == null || "".equals(data))
            return "";
        String key = "FIXME";
        byte[] end = dec(data);
        try {
            byte[] keys = key.getBytes();
            int datalen = end.length;
            int len = key.length();
            int keyindex = 0;
            for (int srcindex = 0; srcindex < datalen; srcindex++) {
                if (keyindex >= len) {
                    keyindex = 0;
                }
                end[srcindex] = ((byte) (end[srcindex] ^ keys[keyindex]));
                keyindex++;
            }
            return new String(end, CHARSET);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return "";
    }




}
