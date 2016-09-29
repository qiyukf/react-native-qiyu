package com.qiyukf.unicorn.reactnative;

import android.content.Context;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.AsyncTask;
import android.support.annotation.Nullable;

import com.facebook.common.executors.UiThreadImmediateExecutorService;
import com.facebook.common.references.CloseableReference;
import com.facebook.datasource.DataSource;
import com.facebook.drawee.backends.pipeline.Fresco;
import com.facebook.imagepipeline.common.ResizeOptions;
import com.facebook.imagepipeline.core.ImagePipeline;
import com.facebook.imagepipeline.datasource.BaseBitmapDataSubscriber;
import com.facebook.imagepipeline.image.CloseableBitmap;
import com.facebook.imagepipeline.image.CloseableImage;
import com.facebook.imagepipeline.request.ImageRequest;
import com.facebook.imagepipeline.request.ImageRequestBuilder;
import com.qiyukf.unicorn.api.ImageLoaderListener;
import com.qiyukf.unicorn.api.UnicornImageLoader;

/**
 * Created by hzwangchenyan on 2016/4/1.
 */
public class FrescoImageLoader implements UnicornImageLoader {
    private Context context;

    public FrescoImageLoader(Context context) {
        this.context = context.getApplicationContext();
    }

    @Override
    public Bitmap loadImageSync(String uri, int width, int height) {
        Bitmap resultBitmap = null;
        ImagePipeline imagePipeline = Fresco.getImagePipeline();
        boolean inMemoryCache = imagePipeline.isInBitmapMemoryCache(Uri.parse(uri));
        if (inMemoryCache) {
            ImageRequestBuilder builder = ImageRequestBuilder.newBuilderWithSource(Uri.parse(uri));
            if (width > 0 && height > 0) {
                builder.setResizeOptions(new ResizeOptions(width, height));
            }
            ImageRequest imageRequest = builder.build();
            DataSource<CloseableReference<CloseableImage>> dataSource = imagePipeline.fetchImageFromBitmapCache(imageRequest, context);
            CloseableReference<CloseableImage> imageReference = null;
            try {
                imageReference = dataSource.getResult();
                if (imageReference != null) {
                    CloseableImage closeableImage = imageReference.get();
                    if (closeableImage != null && closeableImage instanceof CloseableBitmap) {
                        resultBitmap = (((CloseableBitmap) closeableImage).getUnderlyingBitmap()).copy(Bitmap.Config.RGB_565, false);
                    }
                }
            } finally {
                dataSource.close();
                CloseableReference.closeSafely(imageReference);
            }
        }
        return resultBitmap;
    }

    @Override
    public void loadImage(String uri, int width, int height, final ImageLoaderListener listener) {
        ImageRequestBuilder builder = ImageRequestBuilder.newBuilderWithSource(Uri.parse(uri));
        if (width > 0 && height > 0) {
            builder.setResizeOptions(new ResizeOptions(width, height));
        }
        ImageRequest imageRequest = builder.build();

        ImagePipeline imagePipeline = Fresco.getImagePipeline();
        DataSource<CloseableReference<CloseableImage>> dataSource = imagePipeline.fetchDecodedImage(imageRequest, context);

        dataSource.subscribe(new BaseBitmapDataSubscriber() {
                                 @Override
                                 public void onNewResultImpl(@Nullable Bitmap bitmap) {
                                     if (listener != null && bitmap != null) {
                                         BitmapCopyAsyncTask bitmapCopyAsyncTask = new BitmapCopyAsyncTask(bitmap);
                                         bitmapCopyAsyncTask.setOnDataFinishedListener(new OnDataFinishedListener() {
                                             @Override
                                             public void onSucceed(Object data) {
                                                 listener.onLoadComplete((Bitmap) data);
                                             }

                                             @Override
                                             public void onFailed() {
                                                 listener.onLoadFailed(null);
                                             }
                                         });
                                         bitmapCopyAsyncTask.execute();
                                     }
                                 }

                                 @Override
                                 public void onFailureImpl(DataSource dataSource) {
                                     if (listener != null) {
                                         listener.onLoadFailed(dataSource.getFailureCause());
                                     }
                                 }
                             },
                UiThreadImmediateExecutorService.getInstance());
    }

    private class BitmapCopyAsyncTask extends AsyncTask<Void, Void, Bitmap> {
        private Bitmap originBitmap;
        private OnDataFinishedListener onDataFinishedListener;

        public BitmapCopyAsyncTask(Bitmap originBitmap) {
            this.originBitmap = originBitmap;
        }

        @Override
        protected Bitmap doInBackground(Void... params) {
            Bitmap resultBitmap = null;
            if (originBitmap != null) {
                resultBitmap = originBitmap.copy(Bitmap.Config.RGB_565, false);
            }
            return resultBitmap;
        }

        @Override
        protected void onPostExecute(Bitmap bitmap) {
            super.onPostExecute(bitmap);
            if (bitmap != null) {
                onDataFinishedListener.onSucceed(bitmap);
            } else {
                onDataFinishedListener.onFailed();
            }
        }

        public void setOnDataFinishedListener(OnDataFinishedListener onDataFinishedListener) {
            this.onDataFinishedListener = onDataFinishedListener;
        }
    }

    public interface OnDataFinishedListener {
        void onSucceed(Object data);

        void onFailed();
    }
}
