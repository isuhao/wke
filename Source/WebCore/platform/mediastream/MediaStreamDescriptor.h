/*
 * Copyright (C) 2011 Ericsson AB. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer
 *    in the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of Ericsson nor the names of its contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef MediaStreamDescriptor_h
#define MediaStreamDescriptor_h

#if ENABLE(MEDIA_STREAM)

#include "MediaStreamComponent.h"
#include <wtf/RefCounted.h>
#include <wtf/Vector.h>

namespace WebCore {

class MediaStream;

class MediaStreamDescriptor : public RefCounted<MediaStreamDescriptor> {
public:
    static PassRefPtr<MediaStreamDescriptor> create(const String& label, const MediaStreamSourceVector& sources)
    {
        return adoptRef(new MediaStreamDescriptor(label, sources));
    }

    MediaStream* owner() const { return m_owner; }
    void setOwner(MediaStream* owner) { m_owner = owner; }

    String label() const { return m_label; }

    MediaStreamComponent* component(unsigned index) const { return m_components[index].get(); }
    unsigned numberOfComponents() const { return m_components.size(); }

    bool ended() const { return m_ended; }
    void setEnded() { m_ended = true; }

private:
    MediaStreamDescriptor(const String& label, const MediaStreamSourceVector& sources)
        : m_owner(0)
        , m_label(label)
        , m_ended(false)
    {
        for (size_t i = 0; i < sources.size(); i++)
            m_components.append(MediaStreamComponent::create(sources[i]));
    }

    MediaStream* m_owner;
    String m_label;
    Vector<RefPtr<MediaStreamComponent> > m_components;
    bool m_ended;
};

typedef Vector<RefPtr<MediaStreamDescriptor> > MediaStreamDescriptorVector;

} // namespace WebCore

#endif // ENABLE(MEDIA_STREAM)

#endif // MediaStreamDescriptor_h
