// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_PLATFORM_GRAPHICS_PAINT_DRAWING_RECORDER_H_
#define THIRD_PARTY_BLINK_RENDERER_PLATFORM_GRAPHICS_PAINT_DRAWING_RECORDER_H_

#include "third_party/blink/renderer/platform/platform_export.h"

#include "third_party/blink/renderer/platform/geometry/float_rect.h"
#include "third_party/blink/renderer/platform/geometry/layout_rect.h"
#include "third_party/blink/renderer/platform/graphics/graphics_context.h"
#include "third_party/blink/renderer/platform/graphics/paint/drawing_display_item.h"
#include "third_party/blink/renderer/platform/graphics/paint/paint_controller.h"
#include "third_party/blink/renderer/platform/wtf/allocator.h"
#include "third_party/blink/renderer/platform/wtf/auto_reset.h"
#include "third_party/blink/renderer/platform/wtf/noncopyable.h"

namespace blink {

class GraphicsContext;

class PLATFORM_EXPORT DrawingRecorder final {
  DISALLOW_NEW_EXCEPT_PLACEMENT_NEW();
  WTF_MAKE_NONCOPYABLE(DrawingRecorder);

 public:
  static bool UseCachedDrawingIfPossible(GraphicsContext& context,
                                         const DisplayItemClient& client,
                                         DisplayItem::Type type) {
    return context.GetPaintController().UseCachedDrawingIfPossible(client,
                                                                   type);
  }

  static bool UseCachedDrawingIfPossible(GraphicsContext& context,
                                         const DisplayItemClient& client,
                                         PaintPhase phase) {
    return UseCachedDrawingIfPossible(
        context, client, DisplayItem::PaintPhaseToDrawingType(phase));
  }

  DrawingRecorder(GraphicsContext&,
                  const DisplayItemClient&,
                  DisplayItem::Type);

  DrawingRecorder(GraphicsContext& context,
                  const DisplayItemClient& client,
                  PaintPhase phase)
      : DrawingRecorder(context,
                        client,
                        DisplayItem::PaintPhaseToDrawingType(phase)) {}

  ~DrawingRecorder();

  void SetKnownToBeOpaque() {
    DCHECK(RuntimeEnabledFeatures::SlimmingPaintV2Enabled());
    known_to_be_opaque_ = true;
  }

 private:
  GraphicsContext& context_;
  const DisplayItemClient& client_;
  const DisplayItem::Type type_;

  // True if there are no transparent areas. Only used for SlimmingPaintV2.
  bool known_to_be_opaque_;

#if DCHECK_IS_ON()
  // Ensures the list size does not change during the recorder's scope.
  size_t initial_display_item_list_size_;
#endif
};

#if DCHECK_IS_ON()
class DisableListModificationCheck {
  STACK_ALLOCATED();
  WTF_MAKE_NONCOPYABLE(DisableListModificationCheck);

 public:
  DisableListModificationCheck();

 private:
  AutoReset<bool> disabler_;
};
#endif  // DCHECK_IS_ON()

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_PLATFORM_GRAPHICS_PAINT_DRAWING_RECORDER_H_
